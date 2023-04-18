/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** delete
*/

#include "socket.h"

int dele_cmd(ftp_s *ftp)
{
    if (!ftp->connection)
        write_message(ftp->client, "530 Please login with USER and PASS.\r\n");
    else if (ftp->all_commands[1] == NULL)
        write_message(ftp->client, "550 Permission denied.\r\n");
    else {
        if (remove(ftp->all_commands[1]) < 0)
            write_message(ftp->client, "550 Permission denied.\r\n");
        else
            write_message(ftp->client, "250 Requested file action okay,"
            " completed.\r\n");
    }
    return EXIT_SUCCESS;
}