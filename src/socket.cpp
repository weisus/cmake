#include "socket.h"
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

mtd::ipAddr::ipAddr(IP_TYPE type, const char* ip, unsigned short port) {
    addr.sin_family = type == IPV4 ? AF_INET : AF_INET6;
    addr.sin_port = ::htons(port);
    ::inet_pton(type == IPV4 ? AF_INET : AF_INET6, ip, &addr.sin_addr.s_addr);
}

void mtd::ipAddr::setAddr(IP_TYPE type, const char* ip, unsigned short port) {
    addr.sin_family = type == IPV4 ? AF_INET : AF_INET6;
    addr.sin_port = ::htons(port);
    ::inet_pton(type == IPV4 ? AF_INET : AF_INET6, ip, &addr.sin_addr.s_addr);
}

void mtd::ipAddr::setIp(IP_TYPE type, const char* ip) {
    ::inet_pton(type == IPV4 ? AF_INET : AF_INET6, ip, &addr.sin_addr.s_addr);
}

void mtd::ipAddr::setPort(unsigned short port) {
    addr.sin_port = ::htons(port);
}

unsigned short mtd::ipAddr::getPort() const {
    return ::ntohs(addr.sin_port);
}

const char* mtd::ipAddr::getIp() const {
    return ::inet_ntoa(addr.sin_addr);
}

mtd::IP_TYPE mtd::ipAddr::getIpType() const {
    return addr.sin_family == AF_INET ? IPV4 : IPV6;
}

mtd::socket::socket(SOCKET_TYPE type): fd(-1), stype(type) {}

mtd::socket::socket(socket&& s): fd(s.fd), stype(s.stype) {
    s.fd = -1;
}

mtd::socket::socket(int fd, SOCKET_TYPE stype): fd(fd), stype(stype) {}

mtd::socket::~socket() {
    // if (fd != -1) {
    //     ::close(fd);
    //     fd = -1;
    // }
}

int mtd::socket::getFd() const {
    return fd;
}

mtd::SOCKET_TYPE mtd::socket::getSocketType() const {
    return stype;
}

int mtd::socket::listen(ipAddr addr, int backlog) {
    fd = ::socket(addr.addr.sin_family, stype == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
    if (fd == -1) {
        return -1;
    }
    int ret = ::bind(fd, (struct sockaddr*)&addr.addr, sizeof(addr.addr));
    if (ret == -1) {
        return -1;
    }

    ret = ::listen(fd, backlog);
    if (ret == -1) {
        return -1;
    }

    return ret;
}

int mtd::socket::listen(IP_TYPE type, const char* ip, unsigned short port, int backlog) {
    mtd::ipAddr addr(type, ip, port);
    return listen(addr, backlog);
}

mtd::socket mtd::socket::accept() const {
    int cfd = ::accept(fd, nullptr, 0);
    if (cfd == -1) {
        return mtd::socket();
    }
    return mtd::socket(cfd, stype);
}

mtd::socket mtd::socket::accept(ipAddr& addr) const {
    struct sockaddr_in caddr;
    int addrlen = sizeof(struct sockaddr_in);
    int cfd = ::accept(fd, (struct sockaddr*)&caddr, (socklen_t*)&addrlen);
    if (cfd == -1) {
        return mtd::socket();
    }
    addr.addr = caddr;
    return mtd::socket(cfd, stype);
}

int mtd::socket::connect(const ipAddr& addr) {
    fd = ::socket(addr.addr.sin_family, stype == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
    return ::connect(fd, (struct sockaddr*)&addr.addr, sizeof(addr.addr));
}

int mtd::socket::connect(IP_TYPE type, const char* ip, unsigned short port) {
    mtd::ipAddr addr(type, ip, port);
    return connect(addr);
}

int mtd::socket::send(const char* msg, int len) const {
    int sendLen = ::htonl(len);
    int size = ::send(fd, (char*)&sendLen, 4, 0);
    if (size != 4) {
        return -1;
    }
    return ::send(fd, msg, len, 0);
}

int mtd::socket::recv(char* msg, int len) const {
    int recvLen = 0;
    int size = ::recv(fd, (char*)&recvLen, 4, 0);
    if (size != 4) {
        return -1;
    }
    recvLen = ::ntohl(recvLen);
    recvLen = recvLen > len ? len : recvLen;
    return ::recv(fd, msg, recvLen, 0);
}

void mtd::socket::close() {
    ::close(fd);
}
