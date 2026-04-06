#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
/*
2. Networking: The "Heartbeat" Monitor
This bridges Beej's socket basics with OSTEP's process/thread management.

The Task: Write a "Watcher" server and multiple "Client" nodes.

The Logic: Each client connects to the server and sends a "HEARTBEAT" string every 2 seconds.

*/

#define PORT 8080
typedef struct
{
    int server_fd;
    struct sockaddr *address;
    socklen_t addrlen;
} CON;

void* process_accept(void *con)
{
    char *hello = "HELLO MA FRIEND";
    CON *myCon = (CON *)con;
    int new_socket;
    if ((new_socket = accept(myCon->server_fd, (struct sockaddr *)myCon->address, (socklen_t *)&myCon->addrlen)) < 0)
    {
        perror("Accept");
        exit(EXIT_FAILURE);
    }
    sleep(1);

    send(new_socket, hello, strlen(hello), 0);
    printf("[SINGLE_THREADED] - Hello message sent\n");
    close(new_socket);
}

int main()
{
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        CON con = {
            .server_fd = server_fd,
            .address = (struct sockaddr *)&address,
            .addrlen = sizeof(addrlen)};
        process_accept(&con);
    }

    return 0;
}