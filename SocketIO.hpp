#ifndef SOCKETIO_H
#define SOCKETIO_H
#include "Socket.hpp"
#include <vector>
#include <string>


namespace zcs{
    class SocketIO{
        public:
            explicit SocketIO(Socket &socket);//根据传入的socket对象进行构造
            ssize_t read(char* buf,size_t size);//从socket中读取数据并返回实际读取到的字节数
            ssize_t write(const char* buf,size_t size);//向socket中写入数据返回实际写入的字节数
            std::string readline();//按行读取，直到遇到\n为止，返回读取的行
        private:
            Socket &_socket;
            std::vector<char> _buffer;//内部缓冲区，用于判断当前读取内容合规
    };
}


#endif