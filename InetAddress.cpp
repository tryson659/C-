#include "InetAddress.hpp"
#include <cstring>

namespace zcs{

    InetAddress::InetAddress(const string& ip,unsigned short port){
        ::memset(&_addr,0,sizeof(struct sockaddr_in));
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(port);
        inet_pton(AF_INET,ip.c_str(),&_addr.sin_addr);
    }

    InetAddress::InetAddress(unsigned short port)
    {
        ::memset(&_addr, 0, sizeof(struct sockaddr_in));
        _addr.sin_family = AF_INET;  //小端模式      大端模式
        _addr.sin_port = htons(port);//主机字节序转成网络字节序列
        _addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("0.0.0.0") 代表本机地址(一个服务器可能有多个网卡)
    }

    InetAddress::InetAddress(const struct sockaddr_in & addr)
    :_addr(addr)
    {
    }
    struct sockaddr_in * InetAddress::getInetAddress(){
        return &_addr;
    }
    string InetAddress::getIp() const{
        char str[INET_ADDRSTRLEN] = {0};
        ::inet_ntop(AF_INET, const_cast<in_addr*>(&_addr.sin_addr), str, sizeof(str));
        return std::string(str);

    }
    unsigned short InetAddress::getPort() const{
        return ntohs(_addr.sin_port);
    }

}