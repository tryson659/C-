#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "Socket.hpp"
#include "SocketIO.hpp"
#include "InetAddress.hpp"

#include <memory>
#include <string>


namespace zcs
{
    class TcpConnection{
        public:

        explicit TcpConnection(int fd); // 从 accept 得到的新 fd 创建连接
        ~TcpConnection();

        // 接收数据（封装 readline）
        std::string receive();

        // 发送数据（封装 writen）
        void send(const std::string& msg);

        // 主动关闭连接（关闭写端）
        void shutdown();

        // 判断连接是否已关闭
        bool isClosed() const;

        // 获取本地 / 对端地址
        std::string toString() const;

        private:
        InetAddress getLocalAddr(int sockfd);
        InetAddress getPeerAddr(int sockfd);
        private:
        int _fd;
        std::unique_ptr<SocketIO> _sockIO;
        InetAddress _localAddr;
        InetAddress _peerAddr;
        bool _isShutdownWrite;
    };
} 



#endif