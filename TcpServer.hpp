#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "EventLoop.hpp"

#include <memory>
#include <map>
#include <string>

namespace zcs
{
    class TcpServer{
        public:
        TcpServer(const std::string& ip, unsigned short port);
        ~TcpServer();
    
        void start(); 
        private:
        void onNewConnection();
        void onMessage(int fd);
        void onClose(int fd);   
        private:
        Acceptor _acceptor;
        EventLoop _loop;
        std::map<int, std::shared_ptr<TcpConnection>> _conns; 
    };
} 
#endif