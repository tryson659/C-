#ifndef SOCKET_H
#define SOCKET_H

namespace zcs{
    class Socket{
        public:
            Socket();//创建socket
            ~Socket();//自动关闭socket
            explicit Socket(int fd);//用已有的fd进行构造
            int fd()const;//获取底层套接字
            void shutdownWrite();//关闭写端
        private:
            int _fd;
    };
}

#endif