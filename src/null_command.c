/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** null_command
*/

#include "socket.h"

void manage_null_command(ftp_s *ftp)
{
    char *dontlogin = "530 Please login with USER and PASS.\r\n";
    char *commandnotfound = "500 Unknown Command.\r\n";

    if (!ftp->connection) {
        write(ftp->client, dontlogin, strlen(dontlogin));
    } else {
        write(ftp->client, commandnotfound, strlen(commandnotfound));
    }
}