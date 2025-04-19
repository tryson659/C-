#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "Epoller.hpp"

#include <map>
#include <functional>
#include <vector>


namespace zcs{
    class EventLoop{
        public:
        using Functor = std::function<void()>;

        EventLoop();
        ~EventLoop();

        void loop(int fd); // 主事件循环
        void unloop(); // 停止事件循环

         // 添加事件处理回调
        void setNewConnectionCallback(Functor cb) {
            _onNewConnection = std::move(cb);
        }

        void setMessageCallback(Functor cb) {
            _onMessage = std::move(cb);
        }

        void setCloseCallback(Functor cb) {
            _onClose = std::move(cb);
        }
        void registerConnectionFd(int fd) {
            _poller->addFd(fd);
        }


        private:
        bool _isLooping;
        int _epfd;
        Functor _onNewConnection;
        Functor _onMessage;
        Functor _onClose;
        Epoller* _poller;
    
    };
} 

#endif