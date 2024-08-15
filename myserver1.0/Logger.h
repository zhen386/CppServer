#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdarg>  // 处理可变参数的头文件

enum Loglevel {
    INFO,
    WARNING,
    ERROR
};

// Logger类，用于执行日志记录操作
class Logger {
public:
    static void logMessage(Loglevel level, const char* format, ...){
        std::ofstream logFile("server.log", std::ios::app);

        // 获取当前时间  
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);

        // 根据日志级别确定字符串
        std::string levelStr;
        switch (level) {
            case INFO: levelStr = "INFO"; break;
            case WARNING: levelStr = "WARNING"; break;
            case ERROR: levelStr = "ERROR"; break;
        }

        va_list args; 
        va_start(args, format);
        char buffer[2048];
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        // 将时间戳、日志级别和格式化后的日志信息写入日志文件
        logFile << std::ctime(&now_c) << " [" << levelStr << "] " << buffer << std::endl;

        // 关闭日志文件
        logFile.close();

    }
};

#define LOG_INFO(...) Logger::logMessage(INFO, __VA_ARGS__)
#define LOG_WARNING(...) Logger::logMessage(WARNING, __VA_ARGS__)
#define LOG_ERROR(...) Logger::logMessage(ERROR, __VA__ARGS__)

// 调用LOG_INFO(“Hello, %s", name)时，编译器通过宏定义替换为Logger::logMessage(INFO, "Hello, %s", name)，简化使用
