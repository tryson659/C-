#include "SocketIO.hpp"
#include <unistd.h>  // read, write
#include <errno.h>
#include <cstring>   // memcpy, memset
namespace zcs{
    SocketIO::SocketIO(int fd)
    : _fd(fd) {}

    // 阻塞读取 len 字节
    int SocketIO::readn(char* buf, int len) {
        int left = len;
        char* p = buf;

        while (left > 0) {
            int nread = ::read(_fd, p, left);
            if (nread == -1) {
                if (errno == EINTR) continue; // 被信号中断，继续读
                return -1;
            } else if (nread == 0) {
                break; // 对方关闭
            }

            left -= nread;
            p += nread;
        }

        return len - left; // 实际读了多少
    }

    // 阻塞写入 len 字节
    int SocketIO::writen(const char* buf, int len) {
        int left = len;
        const char* p = buf;

        while (left > 0) {
            int nwrite = ::write(_fd, p, left);
            if (nwrite == -1) {
                if (errno == EINTR) continue;
                return -1;
            }

            left -= nwrite;
            p += nwrite;
        }

        return len;
    }

    // 一行一行读取，直到 '\n'（包含它）或读取了 maxlen - 1 个字符（留出 '\0'）
    int SocketIO::readline(char* buf, int maxlen) {
        int total = 0;
        char c = 0;

        while (total < maxlen - 1) {
            int nread = ::read(_fd, &c, 1);
            if (nread == -1) {
                if (errno == EINTR) continue;
                return -1;
            } else if (nread == 0) {
                break; // 对方关闭连接
            }

            buf[total++] = c;

            if (c == '\n') break; // 读到一行结束
        }

        buf[total] = '\0'; // 字符串终止符
        return total;
    }
}
