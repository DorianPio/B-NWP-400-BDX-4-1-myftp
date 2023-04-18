/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** noop
*/

#include "socket.h"

int noop_cmd(ftp_s *ftp)
{
    if (ftp->all_commands == NULL || !ftp->connection) {
        write_message(ftp->client, "530 Please login with USER and PASS.\r\n");
    } else {
        write_message(ftp->client, "200 Command okay.\r\n");
    }
}