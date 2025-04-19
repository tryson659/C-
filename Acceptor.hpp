#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "InetAddress.hpp"
#include "Socket.hpp"

namespace zcs
{
    class Acceptor{
        public:
            Acceptor(const std::string &ip,unsigned short port);
            void bind();//绑定地址
            void listen();//监听
            void setReuseAddr();//地址重用
            void setReusePort();//端口重用
            int accept();//接收连接
            void ready();
            int fd();

        private:
        zcs::InetAddress _addr;//封装ip和端口
        zcs::Socket _sock;//封装底层socketfd
    };
} 



#endif