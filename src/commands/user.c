/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** username
*/

#include "socket.h"

int user_cmd(ftp_s *ftp)
{
    if (!ftp->all_commands || my_strlen(ftp->all_commands[1]) == 0) {
        write_message(ftp->client, "530 Permission denied.\r\n");
        return EXIT_FAILURE;
    } else {
        if (ftp->username)
            free(ftp->username);
        ftp->username = strdup(ftp->all_commands[1]);
        write_message(ftp->client, "331 User name okay, need password.\r\n");
    }
    return EXIT_SUCCESS;
}