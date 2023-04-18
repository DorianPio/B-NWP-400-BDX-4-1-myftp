/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** list
*/

#include "socket.h"

int list_cmd(ftp_s *ftp)
{
    int dup_ = 0;

    if (!ftp->connection)
        write_message(ftp->client, "530 Please login with USER and PASS.\r\n");
    else if (ftp->mode == NONE)
        write_message(ftp->client, "425 Use PORT or PASV first.\r\n");
    else {
        write_message(ftp->client, LIST);
        ftp->mode = NONE;
        dup_ = dup(1);
        dup2(ftp->transmission, 1);
        system("ls -l | grep -v ^d | grep -v ^total");
        dup2(dup_, 1);
        close(dup_);
        stop_socket(ftp->transmission);
        write_message(ftp->client, "226 Closing data connection.\r\n");
    }
    return EXIT_SUCCESS;
}