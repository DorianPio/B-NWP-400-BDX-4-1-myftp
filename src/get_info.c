/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** get_info
*/

#include "socket.h"

char *get_info(ftp_s *ftp, char **ip)
{
    char *result = malloc(sizeof(char) * 1024);

    memset(result, 0, 1024);
    sprintf(result, "227 Entering Passive Mode (%s, %s, %s, %s, %d, %d, %d)."
    "\r\n", ip[0], ip[1], ip[2], ip[3], ftp->transmission_port / 256,
    ftp->transmission_port % 256);
    return result;
}