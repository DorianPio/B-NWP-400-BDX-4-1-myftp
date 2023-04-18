/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** create_socket
*/

#include "socket.h"

int create_socket()
{
    t_protoent *sock = getprotobyname("TCP");
    int fd = 0;

    if (!sock) {
        printf("getprotobyname failed\n");
        return EXIT_FAILURE;
    }
    fd = socket(AF_INET, SOCK_STREAM, sock->p_proto);
    if (fd < 0) {
        printf("socket failed\n");
        return EXIT_FAILURE;
    }
    return fd;
}