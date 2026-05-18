#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

void *process_accept(void *socket_ptr)
{
    int newSocket = *((int *)socket_ptr);
    free(socket_ptr);

    char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";

    sleep(1);
    send(newSocket, hello, strlen(hello), 0);
    printf("[MULTITHREADED] - [THREAD %lu] - Resposta enviada\n", pthread_self());

    close(newSocket);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s <porta>\n", argv[0]);
        return 1;
    }

    int MYPORT = atoi(argv[1]);
    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(MYPORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor rodando na porta %d...\n", MYPORT);

    int max_fd, client_socket[MAX_CLIENTS] = {0}, activity, valread;
    fd_set readfds;

    char buffer[1024];

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_fd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            int cs = client_socket[i];
            if (cs > 0)
                FD_SET(cs, &readfds);
            if (cs > max_fd)
                max_fd = cs;
        }

        activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0)
            printf("Select error\n");

        if (FD_ISSET(server_fd, &readfds))
        {
            socklen_t addrlen = sizeof(address);
            int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            printf("New connection on father socket[%d]\n", new_socket);

            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            int cs = client_socket[i];

            if (FD_ISSET(cs, &readfds))
            {
                if ((valread = read(cs, buffer, 1024)) == 0)
                {
                    client_socket[i] = 0;
                    close(cs);
                    char *answer = "I was here before!";
                    send(cs, answer, strlen(answer), 0);
                    printf("Host disconnected, fd %d\nAnswer: %s\n", cs, answer);
                }
                else
                {
                    printf("Client says %s", buffer);
                    char *answer = "I was here before!";
                    send(cs, answer, strlen(answer), 0);
                }
            }
        }
    }
    return 0;
}
