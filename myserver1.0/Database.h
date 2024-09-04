#include <sqlite3.h>
#include <iostream>

#include "Logger.h"

class Database{
private:
    sqlite3* db;

public:
    // 构造函数，打开数据库并创建用户

    Database(const std::string& db_path){

        // 使用sqlite3_open打开数据库
        // db_path.c_str()将cpp字符串转换为c字符串，sqlite3_open()仅接受c风格的字符串
        // &db是指向数据库连接对象的指针
        if(sqlite3_open(db_path.c_str(), &db) != SQLITE_OK){
            // 打开失败则抛出运行时错误
            throw std::runtime_error("Failed to open database");
        }

        // 定义创建用户表的SQL语句
        const char* sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT);";
        char* errmsg;

        // 执行SQL语句创建表
        // db是数据库连接对象，sql是待执行的SQL语句
        // 后续参数是回调函数和他的参数，此处不需要
        if(sqlite3_exec(db, sql, 0, 0, &errmsg) != SQLITE_OK){
            //若创建表失败，则抛出运行时错误，并附带显示错误信息
            throw std::runtime_error("Failed to create table: " + std::string(errmsg));
        }

    }

    ~Database(){
        // 关闭数据库连接
        sqlite3_close(db);
    }

    bool registerUser(const std::string& username, const std::string& password){
        // 用于插入新用户的SQL语句
        std::string sql = "INSERT INTO users (username, password) VALUES (?, ?);";
        sqlite3_stmt* stmt;

        // 预编译SQL语句以防止注入攻击
        if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
            // 准备SQL语句失败，记录日志并返回错false
            LOG_INFO("Failed to prepare registeration SQL for user: %s", username.c_str());
            return false;
        }

        // 绑定SQL语句中的参数，防止SQL注入
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

        if(sqlite3_step(stmt) != SQLITE_DONE){
            // 如果执行失败，记录日志，清理资源并返回false
            LOG_INFO("Registration failed for user: %s", username.c_str());
            sqlite3_finalize(stmt);
            return false;
        }

        // 清理资源，关闭SQL语句
        sqlite3_finalize(stmt);
        // 注册用户成功，写入日志，此处写入用户名和密码仅为方便示意，不建议在日志中写入任何敏感信息
        LOG_INFO("User registered: %s with password: %s", username.c_str(), password.c_str());
        return true;
    }

    bool loginUser(const std::string& username, const std::string& password){
        // 构建查询用户密码的SQL语句
        std::string sql = "SELECT password FROM users WHERE username = ?;";
        sqlite3_stmt* stmt;

        // 准备SQL语句
        if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
            LOG_INFO("Failed to prepare login SQL for user: %s", username.c_str());
            return false;
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        // 执行SQL语句
        if(sqlite3_step(stmt) != SQLITE_ROW){
            LOG_INFO("User not found: %s", username.c_str());
            sqlite3_finalize(stmt);
            return false;
        }

        // 获取查询结果中的密码
        const char* stored_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        std::string password_str(stored_password, sqlite3_column_bytes(stmt,0));

        //检查密码是否匹配
        sqlite3_finalize(stmt);
        if(stored_password == nullptr || password != password_str){
            //密码不匹配，记录日志并返回false
            LOG_INFO("Login failed for user: %s, password: %s, stored password is: %s", username.c_str(), password.c_str(), password_str.c_str());
            return false;

        }

        // 登录成功，记录日志
        LOG_INFO("User logged in: %s", username.c_str());
        return true;
    }

};