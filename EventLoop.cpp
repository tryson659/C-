#include "EventLoop.hpp"

namespace zcs
{
    // bool _isLooping;
    // int _epfd;
    // Functor _onNewConnection;
    // Functor _onMessage;
    // Functor _onClose;
    // Epoller* _epoller;
    EventLoop::EventLoop():_isLooping(false),_poller(new Epoller()){

    }

    EventLoop::~EventLoop(){
        if (_poller) {
            delete _poller;
        }
    }

    void EventLoop::loop(int fd){
        _isLooping = true;
        _poller->setListenFd(fd);
        while (_isLooping)
        {
            std::vector<int> activeFds = _poller->wait();
            for(int fd : activeFds){
                if (fd == _poller->getListenFd())
                {
                    if(_onNewConnection)_onNewConnection();
                }else{
                    if (_poller->isConnectionClosed(fd))
                    {
                        if (_onClose) _onClose(); 
                    }else{
                        if (_onMessage)_onMessage();
                    }
                }
            }
        }
        
    }
    void EventLoop::unloop(){
        _isLooping = false;
    }
}
