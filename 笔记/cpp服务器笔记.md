# Docker

## Dockerfile创建镜像

```dockerfile
FROM ubuntu:latest

RUN sed -i 's/http:\/\/ports.ubuntu.com/https:\/\/mirrors.ustc.edu.cn/ubuntu/g' /etc/apt/sources.list

RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential python3 python3-pip libsqlite3-dev curl && \
    rm -rf /var/lib/apt/lists/*

COPY . /usr/src/myapp

WORKDIR /usr/src/myapp

EXPOSE 80 8080 8081
```

FROM 从指定的镜像继承

RUN 在创建镜像的同时运行的命令

COPY 将本机文件复制到镜像指定路径  `COPY SOURCE DEST`

WORKDIR 指定工作目录

EXPOSE 暴露端口，该指令仅作声明使用，告诉开发者需要监听容器的哪些端口。因此使用EXPOSE命令后并不会真正把声明的端口暴露出来，想要从容器外访问端口，则需要在启动容器时使用-p命令指定端口映射关系。EXPOSE中声明的端口也会在docker客户端的run选项中体现。![image-20240729083329082](/Users/zhen/Library/Application Support/typora-user-images/image-20240729083329082.png)