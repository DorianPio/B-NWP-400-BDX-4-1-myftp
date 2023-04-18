/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** close_with_mode
*/

#include "socket.h"

void close_with_mode(ftp_s *ftp)
{
    if (ftp->mode == NONE)
        stop_socket(ftp->transmission);
    if (ftp->mode == PASSIVE)
        stop_socket(ftp->transmission_socket);
}