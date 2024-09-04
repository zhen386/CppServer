#include <iostream>     // 标准输入输出库
#include <map>          // 标准映射容器库
#include <functional>   // 函数对象库，用于定义函数类型
#include <string>       // 字符串处理库
#include <sys/socket.h> // socket编程接口
#include <stdlib.h>     // 标准库。用于通用工具函数    
#include <netinet/in.h> // 网络字节序转换函数
#include <string.h>     // 字符串处理函数
#include <unistd.h>     // UNIX标准函数库
#include "Logger.h"

#define PORT 3531

using RequestHandler = std::function<std::string(const std::string&)>; // 定义请求处理函数类型

std::map<std::string, RequestHandler> get_routes;
std::map<std::string, RequestHandler> post_routes;

void setupRoutes(){

    LOG_INFO("Setting up routes");
    
    // get请求处理表
    get_routes["/"] = [](const std::string& request){
        return "Hello from Macbook air!";
    };

    get_routes["/register"] = [](const std::string& request){
        return "Please use POST to register";
    };

    get_routes["/login"] = [](const std::string& request){
        return "Please use POST to login";
    };

    // post请求处理表
    // post_routes["/"] = [](const std::string& request){
    //     return "Hello from Macbook air!";
    // };

    post_routes["/register"] = [](const std::string& request){
        return "Register Success!";
    };

    post_routes["/login"] = [](const std::string& request){
        return "Login Success!";
    };
}

// 解析http请求
std::pair<std::string, std::string> parseHttpRequest(const std::string& request){
    // 定位第一个空格
    size_t method_end = request.find(" ");
    // 提取http方法
    std::string method = request.substr(0, method_end);

    // 定位第二个空格
    size_t uri_end = request.find(" ", method_end + 1);
    // 提取uri
    std::string uri = request.substr(method_end + 1, uri_end - method_end - 1);

    return {method, uri};
}

// 处理http请求
std::string handlerHttpRequest(const std::string& method, const std::string& uri, const std::string& body){

    LOG_INFO("Handling HTTP request for URI: %s", uri.c_str());

    // 检查GET请求是否在路由表中
    if(method == "GET" && get_routes.count(uri) > 0){
        return get_routes[uri](body);
    }else if(method == "POST" && post_routes.count(uri) > 0){
        return post_routes[uri](body);
    }else{
        return "404 Not Found";
    }
}

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    LOG_INFO("Socket created");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);
    LOG_INFO("Server listening on port %d", PORT);

    setupRoutes();
    LOG_INFO("Server starting");

    while(true){

        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        std::string request(buffer);

        // 解析请求
        auto [method, uri] = parseHttpRequest(request);

        // 处理请求
        std::string response_body = handlerHttpRequest(method, uri, request);

        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n" + response_body;
        send(new_socket, response.c_str(), response.size(), 0);

        close(new_socket);
    }
}