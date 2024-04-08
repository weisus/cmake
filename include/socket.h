#pragma once
#include <netinet/in.h>

namespace mtd {
    enum IP_TYPE {
        IPV4 = 1,
        IPV6 = 2
    };

    enum SOCKET_TYPE {
        TCP = 1,
        UDP = 2
    };

    class ipAddr {
    public:
        ipAddr(IP_TYPE type, const char* ip, unsigned short port);
        void setAddr(IP_TYPE type, const char* ip, unsigned short port);
        void setIp(IP_TYPE type, const char* ip);
        void setPort(unsigned short port);
        unsigned short getPort() const;
        const char* getIp() const;
        IP_TYPE getIpType() const;

        friend class socket;
    private:
        struct sockaddr_in addr;
    };

    class socket {
    public:
        // 构造一个无效的socket，fd = -1
        socket(SOCKET_TYPE type = TCP);
        // socket仅允许移动构造
        socket(socket&& s);
        socket(const socket&) = delete;
        socket& operator=(const socket&) = delete;
        // 析构函数
        ~socket();
        // 获取socket的fd
        int getFd() const;
        // 获取socket的类型
        SOCKET_TYPE getSocketType() const;
        // 用作服务端，监听。backlog为最大连接数。返回值为0表示成功，-1表示失败
        int listen(ipAddr addr, int backlog = 128);
        // 用作服务端，监听。backlog为最大连接数。返回值为0表示成功，-1表示失败
        int listen(IP_TYPE type, const char* ip, unsigned short port, int backlog = 128);
        // 用作服务端，接受客户端连接。返回一个新的socket
        socket accept() const;
        // 用作服务端，接受客户端连接。返回一个新的socket和客户端的ip和端口
        socket accept(ipAddr& addr) const;
        // 用作客户端，连接服务端。返回值为0表示成功，-1表示失败
        int connect(const ipAddr& addr);
        // 用作客户端，连接服务端。返回值为0表示成功，-1表示失败
        int connect(IP_TYPE type, const char* ip, unsigned short port);
        // 发送数据。返回值为实际发送的字节数，-1表示失败，0表示对方关闭连接
        int send(const char* msg, int len) const;
        // 接收数据。返回值为实际接收的字节数，-1表示失败，0表示对方关闭连接
        int recv(char* msg, int len) const;
        // 手动关闭socket，析构函数会自动调用
        void close();
    private:
        socket(int fd, SOCKET_TYPE stype);
        int fd;
        SOCKET_TYPE stype;
    };
}