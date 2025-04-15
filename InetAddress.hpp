//对地址相关进行封装处理
#ifndef INETADDRESS_H
#define INETADDRESS_H

// #include <netinet/in.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
using std::string;

namespace zcs {
    class InetAddress{
        public:
            InetAddress(const string& ip,unsigned short port);//用于ip和端口初始化
            struct sockaddr_in * getInetAddress();//获取封装好的结构体指针
            string getIp() const;
            unsigned short getPort() const;
        private:
            struct sockaddr_in _addr;
    };
}

#endif

