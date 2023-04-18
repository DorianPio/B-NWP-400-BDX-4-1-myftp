/*
** EPITECH PROJECT, 2021
** B-NWP-400-BDX-4-1-myftp-dorian.pio
** File description:
** port_extend
*/

#include "socket.h"

int get_first(char *buf, int *i, int *point)
{
    char *port = malloc(sizeof(char) * 10);
    int result = 0;

    memset(port, 0, 10);
    for (int i2 = 0; buf[*i] && (*point) < 5; (*i++)) {
        if (buf[*i] >= '0' && buf[*i] <= '9') {
            port[i2] = buf[*i];
            i2++;
        } else if (buf[*i] == ',')
            (*point)++;
        else
            return -1;
    }
    result = atoi(port);
    free(port);
    return result;
}