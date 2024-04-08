#include "socket.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    mtd::socket client;
    int ret = client.connect(mtd::IPV4, "127.0.0.1", 10000);
    if (client.getFd() == -1 || ret == -1) {
        perror("connect");
        return -1;
    }
    
    // 通信
    int fd1 = open("../data/english.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return -1;
    }
    int length = 0;
    char tmp[100];
    while ((length = read(fd1, tmp, sizeof(tmp) - 1)) > 0) {
        // 发送数据
        tmp[length] = '\0';
        printf("send: %s\n", tmp);
        length = client.send(tmp, length);
        if (length == -1) {
            perror("send");
            return -1;
        }
        printf("actually send length: %d\n", length);
        usleep(300);
    }
    close(fd1);
    sleep(10);

    return 0;
}