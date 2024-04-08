#include "socket.h"
#include <thread>
#include <unistd.h>
#include <sys/epoll.h>

int working(mtd::socket server);

int main() {
    mtd::socket server;
    int ret = server.listen(mtd::IPV4, "127.0.0.1", 10000);
    if (server.getFd() == -1 || ret == -1) {
        perror("socket");
        return -1;
    }

    int epfd = epoll_create(1);
    if (epfd == -1) {
        perror("epoll_create");
        return -1;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server.getFd();
    epoll_ctl(epfd, EPOLL_CTL_ADD, server.getFd(), &ev);

    struct epoll_event evs[1024];
    int size = sizeof(evs) / sizeof(evs[0]);

    while (true) {
        int num = epoll_wait(epfd, evs, size, -1);
        printf("num: %d\n", num);
        for (int i = 0; i != num; ++i) {
            int fd = evs[i].data.fd;
            if (fd == server.getFd()) {
                mtd::socket newServer = server.accept();
                if (newServer.getFd() == -1) {
                    perror("accept");
                    continue;
                }
                ev.events = EPOLLIN;
                ev.data.fd = newServer.getFd();
                epoll_ctl(epfd, EPOLL_CTL_ADD, newServer.getFd(), &ev);
            } else {
                char buf[1024];
                int len = read(fd, buf, sizeof(buf) - 1);
                if (len == -1) {
                    perror("read");
                    continue;
                } else if (len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                    close(fd);
                    continue;
                } else {
                    buf[len] = '\0';
                    printf("recv: %s\n", buf);
                }
            }
        }
    }

    return 0;
}