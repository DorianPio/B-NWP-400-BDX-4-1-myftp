/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** help
*/

#include "socket.h"

int help_cmd(ftp_s *ftp)
{
    if (ftp->all_commands == NULL || !ftp->connection) {
        write_message(ftp->client, "530 Permission denied.\r\n");
    } else {
        write_message(ftp->client, "214 Help message \n\r");
        for (int i = 0; i < 14; i++) {
            write_message(ftp->client, command_name[i]);
            write_message(ftp->client, " ");
        }
        write_message(ftp->client, "\n");
    }
    return EXIT_SUCCESS;
}