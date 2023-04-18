/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** write_for_the_client
*/

#include "socket.h"

int write_message(int fd, const char *message)
{
    if (message == NULL)
        return EXIT_FAILURE;
    write(fd, message, strlen(message));
    return EXIT_SUCCESS;
}