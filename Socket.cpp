#include "Socket.hpp"
// #include <winsock2.h>
// #include <ws2tcpip.h>
#include <stdexcept>
#include <unistd.h>
#include <sys/socket.h>

namespace zcs {
    Socket::Socket(){
        _fd = ::socket(AF_INET,SOCK_STREAM,0);
        if(_fd == -1){
            throw std::runtime_error("socket create failed");
        }
    }
    Socket::Socket(int fd):_fd(fd){}
    Socket::~Socket(){
        ::close(_fd);
    }

    void Socket::shutdownWrite(){
        ::shutdown(_fd,SHUT_WR);
    }

    int Socket::fd() const{
        return _fd;
    }
}