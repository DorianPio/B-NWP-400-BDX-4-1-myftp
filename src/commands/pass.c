/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** pass
*/

#include "socket.h"

int pass_cmd(ftp_s *ftp)
{
    if (ftp->connection)
        write_message(ftp->client, "230 User logged in, proceed.\r\n");
    else if (ftp->all_commands == NULL || ftp->username == NULL) {
        write_message(ftp->client, "503 Login with USER first.\r\n");
    } else if (strcmp(ftp->username, "Anonymous") == 0) {
        write_message(ftp->client, "230 User logged in, proceed.\r\n");
        ftp->connection = true;
    } else {
        write_message(ftp->client, "530 Login incorrect.\r\n");
        if (ftp->username)
            free(ftp->username);
        ftp->username = NULL;
    }
    return EXIT_SUCCESS;
}