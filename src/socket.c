/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** socket
*/

#include "socket.h"

int stop_socket(int socket)
{
    if (close(socket) == -1) {
        fprintf(stderr, "Failed to close socket\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int start_socket(int socket, char *port)
{
    t_sockaddr sockaddr;
    int port_n = atoi(port);

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port_n);
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket, (struct sockaddr *)&sockaddr,
    sizeof(sockaddr)) == -1) {
        perror("bind() error");
        stop_socket(socket);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int listen_t(int socket, int clients)
{
    if (listen(socket, clients) == -1) {
        fprintf(stderr, "Failed to listen\n");
        stop_socket(socket);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}