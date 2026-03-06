#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define TOTAL 100

int main() {
    struct sockaddr_in server_addr;
    int success = 0;
    int fail = 0;

    for (int i = 0; i < TOTAL; i++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        struct timeval timeout;
        timeout.tv_sec = 3; // 10 seconds
        timeout.tv_usec = 0; // 0 microseconds

        if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof timeout) < 0) {
            perror("setsockopt SO_RCVTIMEO failed");
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(4201);
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
            success++;
            printf("Connected: %d\n", success);
        } else {
            fail++;
            perror("connect");   // prints "connect: Connection timed out"
            printf("Failed: %d (errno=%d)\n", fail, errno);
        }

        // Keep sockets open
        // DO NOT close — we want queue pressure
    }

    printf("Done. Success=%d Fail=%d\n", success, fail);

    sleep(1000);
    return 0;
}