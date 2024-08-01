FROM ubuntu:22.04

ADD sources.list /etc/apt/

#RUN sed -i 's/http:\/\/ports.ubuntu.com/https:\/\/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list

RUN apt-get update

#RUN apt-get install -y --no-install-recommends build-essential python3 python3-pip libsqlite3-dev curl

RUN rm -rf /var/lib/apt/lists/*

COPY . /usr/src/myapp

WORKDIR /usr/src/myapp

EXPOSE 80 3531 8080 8081