#include "TcpConnection.hpp"

#include <unistd.h>
#include <sstream>
#include <cstring>
#include <iostream>

namespace zcs{
    TcpConnection::TcpConnection(int fd):
    _fd(fd)
    , _sockIO(std::make_unique<SocketIO>(_fd))
    , _localAddr(getLocalAddr(_fd))
    , _peerAddr(getPeerAddr(_fd))
    , _isShutdownWrite(false){

    }

    InetAddress TcpConnection::getLocalAddr(int sockfd){
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        ::getsockname(sockfd, (struct sockaddr*)&addr, &len);
        return InetAddress(addr);
    }
    InetAddress TcpConnection::getPeerAddr(int sockfd){
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        ::getpeername(sockfd, (struct sockaddr*)&addr, &len);
        return InetAddress(addr);
    }

    TcpConnection::~TcpConnection(){
        if (!_isShutdownWrite) {
            shutdown();
        }
    }

    std::string TcpConnection::receive(){
        char buf[1024] = {0};//最大接收1024
        int ret = _sockIO->readline(buf,sizeof(buf));
        if (ret == -1) {
            std::cerr << "readline error" << std::endl;
            return "";
        }
        return std::string(buf);
    }

    void TcpConnection::send(const std::string& msg){
        _sockIO->writen(msg.c_str(),msg.size());
    }

    void TcpConnection::shutdown(){
        if (!_isShutdownWrite) {
            ::shutdown(_fd, SHUT_WR);
            _isShutdownWrite = true;
        }
    }

    bool TcpConnection::isClosed() const{
        char buf[1];
        int ret = ::recv(_fd, buf, sizeof(buf), MSG_PEEK);
        return ret == 0;
    }

    std::string TcpConnection::toString() const{
        std::ostringstream oss;
        oss << _localAddr.getIp() << ":" << _localAddr.getPort()
        << " <--> "
        << _peerAddr.getIp() << ":" << _peerAddr.getPort();
    return oss.str();
    }
}