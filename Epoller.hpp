#ifndef EPOLLER_H
#define EPOLLER_H

#include <map>
#include <vector>
#include <sys/epoll.h>

namespace zcs
{
    class Epoller{
        public:
        Epoller();
        ~Epoller();

        void addFd(int fd);              // 添加监听 fd
        void delFd(int fd);              // 移除 fd
        void modFd(int fd, uint32_t ev); // 修改监听事件

        std::vector<int> wait();         // 等待事件，返回活跃 fd
        int getListenFd() const;         // 获取监听 socket（用于判断是否是 accept）
        bool isConnectionClosed(int fd); // 检查连接是否关闭

        void setListenFd(int fd);
        private:
        int _epfd;
        int _listenFd;
        static const int MAX_EVENTS = 1024;
        struct epoll_event _events[MAX_EVENTS];
    };
} // namespace zcs

#endif 