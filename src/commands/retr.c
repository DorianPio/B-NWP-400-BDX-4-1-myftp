/*
** EPITECH PROJECT, 2021
** B-NWP-400-BDX-4-1-myftp-dorian.pio
** File description:
** retr
*/

#include "socket.h"

void retr_next(ftp_s *ftp, int fd)
{
    char *data = malloc(sizeof(char) * 1024);
    int result = read(fd, data, 1024);

    while (result > 0) {
        write(fd, data, result);
        result = read(fd, data, 1024);
    }
    if (result == -1) {
        close(fd);
        perror("read()");
        return;
    }
    write_message(ftp->client, "226 Closing data connection.\r\n");
    close(fd);
}

int retr_cmd(ftp_s *ftp)
{
    int fd = 0;

    if (!ftp->connection)
        return write_message(ftp->client, "530 Please login.\r\n");
    if (ftp->mode == NONE)
        return write_message(ftp->client, "425 Use PORT or PASV first.\r\n");
    if (ftp->all_commands[1] == NULL)
        return write_message(ftp->client, "550 Permission denied.\r\n");
    else {
        fd = open(ftp->all_commands[1], O_RDONLY);
        if (fd < 0)
            return write_message(ftp->client, "550 Permission denied.\r\n");
        write_message(ftp->client, "150 File status okay.");
        retr_next(ftp, fd);
        close(ftp->transmission);
        ftp->mode = NONE;
    }
    return EXIT_SUCCESS;
}