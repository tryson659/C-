#include "Acceptor.hpp"
#include <sys/socket.h> 
#include <unistd.h>
#include <cstring>
#include <stdexcept>

namespace zcs
{
    Acceptor::Acceptor(const std::string &ip,unsigned short port)
    :_addr(ip,port),_sock(){
    }

    void Acceptor::bind(){
        if (::bind(_sock.fd(), (struct sockaddr * )_addr.getInetAddress(), sizeof(struct sockaddr_in)) == -1) {
            throw std::runtime_error("bind failed");
        }
    }
    void Acceptor::listen(){
        if(::listen(_sock.fd(),128) == -1){
            throw std::runtime_error("listen failed");
        }
    }
    void Acceptor::setReuseAddr(){
        int opt = 1;
        ::setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    }
    void Acceptor::setReusePort(){
        int opt = 1;
        ::setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    }
    int Acceptor::accept(){
        int connfd = ::accept(_sock.fd(),NULL,NULL);
        if(connfd == -1){
            throw std::runtime_error("accept failed");
        }
        return connfd;
    }
    
    void Acceptor::ready(){
        setReuseAddr();
        setReusePort();
        bind();
        listen();
    }
    
    int Acceptor::fd(){
        return _sock.fd();
    }
} 
