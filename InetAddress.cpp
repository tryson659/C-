#include "InetAddress.hpp"
#include <cstring>

namespace zcs{

    InetAddress::InetAddress(const string& ip,unsigned short port){
        ::memset(&_addr,0,sizeof(struct sockaddr_in));
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(port);
        inet_pton(AF_INET,ip.c_str(),&_addr.sin_addr);
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