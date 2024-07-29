#include <iostream>     //标准输入输出库
#include <map>          //标准映射容器库
#include <functional>   //函数对象库，用于定义函数类型
#include <string>       //字符串处理库
#include <sys/socket.h> //socket编程接口
#include <stdlib.h>     //标准库。用于通用工具函数    
#include <netinet/in.h> //网络字节序转换函数
#include <string.h>     //字符串处理函数
#include <unistd.h>     //UNIX标准函数库

#define PORT 3531

using RequestHandler = std::function<std::string(const std::string&)>; //定义请求处理函数类型

std::map<std::string, RequestHandler> route_table;

void setupRoutes(){
    route_table["/"] = [](const std::string& request){
        return "Hello from Macbook air!";
    };

    route_table["/register"] = [](const std::string& request){
        return "Register Success!";
    };

    route_table["/login"] = [](const std::string& request){
        return "Login Success!";
    };

    // route_table["/"] = [](const std::string& request){
    //     return "";
    // };
}

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    setupRoutes();

    while(true){

        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        std::string request(buffer);

        std::string uri = request.substr(request.find(" ") + 1);
        uri = uri.substr(0, uri.find(" "));

        std::string response_body;
        if(route_table.count(uri) > 0){
            response_body = route_table[uri](request);
        }else{
            response_body = "404 Not Found";
        }

        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n" + response_body;
        send(new_socket, response.c_str(), response.size(), 0);

        close(new_socket);
    }
}