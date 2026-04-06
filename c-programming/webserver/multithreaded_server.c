#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

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
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        int new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (new_socket < 0)
        {
            perror("Accept");
            continue;
        }

        int *pclient = malloc(sizeof(int));
        *pclient = new_socket;

        pthread_t pthread;
        if (pthread_create(&pthread, NULL, process_accept, pclient) != 0)
        {
            perror("Erro ao criar thread");
            free(pclient);
            close(new_socket);
        }
        pthread_detach(pthread);
    }

    return 0;
}
