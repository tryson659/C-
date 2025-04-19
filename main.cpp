#include "TcpServer.hpp"

int main() {
    std::string ip = "127.0.0.1";
    unsigned short port = 8888;

    zcs::TcpServer server(ip, port);
    server.start(); // 启动服务器，进入事件循环

    return 0;
}
