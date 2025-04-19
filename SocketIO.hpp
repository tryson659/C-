#ifndef SOCKETIO_H
#define SOCKETIO_H
namespace zcs {

    class SocketIO {
    public:
        // 构造：传入 socket 的 fd
        explicit SocketIO(int fd);

        // 阻塞读取 len 字节数据（可能多次调用 read）
        int readn(char* buf, int len);

        // 阻塞写入 len 字节数据（可能多次调用 write）
        int writen(const char* buf, int len);

        // 一行一行读取，直到遇到 '\n' 或达到最大长度
        int readline(char* buf, int maxlen);

    private:
        int _fd; // 套接字文件描述符
    };
}

#endif // SOCKETIO_H