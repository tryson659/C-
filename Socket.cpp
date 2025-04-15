#include "Socket.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>

namespace zcs {
    Socket::Socket(){
        _fd = ::socket(AF_INET,)
    }
    Socket::~Socket(){

    }

    void Socket::shutdownWrite(){

    }

    int Socket::fd() const{
        return _fd;
    }
}