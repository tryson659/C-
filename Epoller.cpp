#include "Epoller.hpp"

#include <unistd.h>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>

namespace zcs
{

    // int _epfd;
    // int _listenFd;
    // static const int MAX_EVENTS = 1024;
    // struct epoll_event _events[MAX_EVENTS];

    Epoller::Epoller():_epfd(::epoll_create1(0)){
        
    }
    Epoller::~Epoller(){
        ::close(_epfd);
    }

    void Epoller::addFd(int fd){
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = EPOLLIN;
        ::epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
    }              
    void Epoller::delFd(int fd){
        ::epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,nullptr);
    }              
    void Epoller::modFd(int fd, uint32_t ev){
        struct epoll_event event;
        event.data.fd = fd;
        event.events = ev;
        ::epoll_ctl(_epfd,EPOLL_CTL_MOD,fd,&event);
    } 

    std::vector<int> Epoller::wait(){
        int nready = ::epoll_wait(_epfd,_events,MAX_EVENTS,-1);
        std::vector<int> activeFds;
        for (int i = 0; i < nready; ++i) {
            activeFds.push_back(_events[i].data.fd);
        }
        return activeFds;
    }         
    int Epoller::getListenFd() const{
        return _listenFd;
    } 
            
    bool Epoller::isConnectionClosed(int fd){
        char buf[1];
        int ret = ::recv(fd,buf,sizeof(buf),MSG_PEEK);
        return ret == 0;
    }

    void Epoller::setListenFd(int fd){
        _listenFd = fd;
        addFd(_listenFd);
    }
} 
