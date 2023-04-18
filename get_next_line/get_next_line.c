/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** get_next_line
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char *result = malloc(sizeof(char) * 2);
    int m = read(fd, result, 1);
    int len = strlen(result);
    char *tmp = malloc(sizeof(char) * 2);

    memset(tmp, 0, 2);
    result[1] = '\0';
    while (result[strlen(result) - 1] != '\n' && m > 0) {
        result = realloc(result, strlen(result) + 1);
        m = read(fd, tmp, 1);
        tmp[1] = '\0';
        result = strcat(result, tmp);
        memset(tmp, 0, 2);
    }
    return result[0] == '\0' ? NULL : result;
}