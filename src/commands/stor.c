/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** stor
*/

#include "socket.h"

int next_stor(ftp_s *ftp, int fd)
{
    char *buffer = malloc(sizeof(char) * 1024);
    int result = 0;

    write_message(ftp->client, LIST);
    for (; result > 0; result = read(ftp->transmission, buffer, 1024)) {
        write(fd, buffer, result);
    }
    if (result < 0) {
        close(fd);
        printf("Read failed");
        return EXIT_FAILURE;
    }
    close(fd);
    return EXIT_SUCCESS;
}

int stor_cmd(ftp_s *ftp)
{
    int fd = 0;

    if (!ftp->connection)
        write_message(ftp->client, LOGIN);
    else if (ftp->mode == NONE)
        write_message(ftp->client, "425 Use PORT or PASV first.\r\n");
    else if (!ftp->all_commands[1])
        write_message(ftp->client, "550 Permission Denied.\r\n");
    else {
        fd = open(ftp->all_commands[1], O_RDWR | O_CREAT);
        if (fd < 0) {
            write_message(ftp->client, "450 Permission denied.\r\n");
            return EXIT_FAILURE;
        }
        next_stor(ftp, fd);
    }
}