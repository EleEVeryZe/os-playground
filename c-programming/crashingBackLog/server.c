#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    int client_fd;
    struct sockaddr_in addr;
    int port = 4201;
    socklen_t addr_len = sizeof(addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 6) < 0) {
        perror("listen");
        exit(1);
    }
    printf("Listening on port %d with backlog=5\n", port);
    printf("NOT calling accept() — queue will fill\n");
    int count = 0;
 
     while (1) {
        int j = 0; 
        while (j < 3) {
       
       client_fd = accept(sockfd, (struct sockaddr*)&addr, &addr_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        j++;
    }
        while (1) {
            sleep(1000);
        }
 
        count++;

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addr.sin_addr, client_ip, INET_ADDRSTRLEN);

        printf("Connection #%d from %s:%d\n",
               count,
               client_ip,
               ntohs(addr.sin_port));

        // Keep connection open (for testing backlog behavior)
        // Comment this close() if you want to hold sockets open
        // close(client_fd);
    }

    close(sockfd);
    return 0;
}