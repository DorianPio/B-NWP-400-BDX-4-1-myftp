/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** clients
*/

#include "socket.h"
#include "signal.h"

int accept_socket(int socket)
{
    t_sockaddr sockaddr;
    socklen_t proto = sizeof(sockaddr);
    int client = accept(socket, (struct sockaddr *)&sockaddr, &proto);

    if (client == -1) {
        fprintf(stderr, "Accept socket error");
        return EXIT_FAILURE;
    }
    return client;
}

int accept_clients(int socket, char *path)
{
    pid_t pid;
    int client = 0;
    int result = 0;

    for (int i = 0; i < CLIENT_MAX; i++) {
        client = accept_socket(socket);
        if (client == EXIT_FAILURE) {
            stop_socket(socket);
            return EXIT_FAILURE;
        }
        pid = fork();
        if (pid == -1) {
            stop_socket(socket);
            return EXIT_FAILURE;
        } else if (pid == 0) {
            result = server_use(socket, client, path);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}