#include "SocketIO.hpp"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

namespace zcs{
    SocketIO::SocketIO(Socket &socket):_socket(socket),_buffer(1024){
    }
    ssize_t SocketIO::read(char *buf,size_t size){
        ssize_t n = ::read(_socket.fd(),buf,size);
        if (n < 0) {
            throw std::runtime_error("Socket read failed");
        }
        return n;
    }

    ssize_t SocketIO::write(){}

    std::string SocketIO::readline(){}
    
}