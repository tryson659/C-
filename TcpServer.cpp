#include "TcpServer.hpp"
#include <iostream>

namespace zcs{
    TcpServer::TcpServer(const std::string& ip, unsigned short port)
    :_acceptor(ip,port)
    {
        _loop.setNewConnectionCallback([this](){
            onNewConnection();
        });
        _loop.setMessageCallback([this](){
            for (auto& conn : _conns) {
                if (!conn.second->isClosed()) {
                    std::string msg = conn.second->receive();
                    if (!msg.empty()) {
                        std::cout << "recv: " << msg;
                        conn.second->send(msg); // 回显
                    }
                }
            }
        });
        _loop.setCloseCallback([this]() {
            for (auto it = _conns.begin(); it != _conns.end(); ) {
                if (it->second->isClosed()) {
                    std::cout << ">> connection closed: " << it->second->toString() << std::endl;
                    it = _conns.erase(it);
                } else {
                    ++it;
                }
            }
        });
    }

    TcpServer::~TcpServer(){

    }


    void TcpServer::start() {
        _acceptor.ready();
        _loop.loop(_acceptor.fd());
    }

    void TcpServer::onNewConnection(){
        int peerfd = _acceptor.accept();
        std::shared_ptr<TcpConnection> conn = std::make_shared<TcpConnection>(peerfd);
        conn->send("welcome to server.\n");
        std::cout << ">> new connection: " << conn->toString() << std::endl;
        _conns[peerfd] = conn;
        _loop.registerConnectionFd(peerfd);
    }
}