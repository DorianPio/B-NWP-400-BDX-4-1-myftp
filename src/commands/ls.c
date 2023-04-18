/*
** EPITECH PROJECT, 2021
** B-NWP-400-BDX-4-1-myftp-dorian.pio
** File description:
** ls
*/

#include "socket.h"
#include <linux/limits.h>

static void read_and_print(ftp_s *ftp)
{
    char *display = malloc(sizeof(char) * PATH_MAX);
    int fd = open(".file", O_RDONLY);
    int m = read(fd, display, 4095);

    display[m] = '\0';
    write_message(ftp->client, display);
    while (m > 0) {
        m = read(fd, display, 4095);
        display[m] = '\0';
        write_message(ftp->client, display);
    }
    free(display);
}

int ls_cmd(ftp_s *ftp)
{
    char *command = malloc(sizeof(char) * PATH_MAX);

    memset(command, 0, PATH_MAX);
    if (!ftp->connection)
        write_message(ftp->client, "530 Please login with USER and PASS.\r\n");
    if (ftp->pwd == NULL) {
        perror("Pwd error");
        return EXIT_FAILURE;
    }
    strcat(command, "ls ");
    if (ftp->all_commands[1] == NULL) {
        strcat(command, ftp->pwd);
    } else
        strcat(command, ftp->all_commands[1]);
    strcat(command, " > .file");
    system(command);
    read_and_print(ftp);
    free(command);
}