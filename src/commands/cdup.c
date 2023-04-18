/*
** EPITECH PROJECT, 2021
** B-NWP-400-BDX-4-1-myftp-dorian.pio
** File description:
** cdup
*/

#include "socket.h"
#include <linux/limits.h>

static int check_error(ftp_s *ftp)
{
    if (!ftp->connection) {
        write_message(ftp->client, "530 Please login with USER and PASS.\r\n");
        return EXIT_FAILURE;
    } else if (ftp->all_commands[1] == NULL) {
        write_message(ftp->client, "550 Failed to change directory.\r\n");
        return EXIT_FAILURE;
    } else {
        if (chdir("..") < 0) {
            write_message(ftp->client, "550 Failed to change directory.\r\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

static void change_directory(ftp_s *ftp)
{
    strcpy(ftp->pwd, ftp->pwd_tmp);
    if (ftp->pwd[0]  == '\0')
        ftp->pwd[0] = '/';
    write_message(ftp->client,
    "250 Requested file action okay, completed.\r\n");
}

int cdup_cmd(ftp_s *ftp)
{
    int fd = ftp->client;

    if (check_error(ftp) == EXIT_FAILURE)
        return EXIT_FAILURE;
    memset(ftp->pwd_tmp, 0, PATH_MAX + 1);
    if (getcwd(ftp->pwd_tmp, PATH_MAX) == NULL) {
        perror("getcwd()");
        return EXIT_FAILURE;
    }
    if (my_strlen(ftp->path) > my_strlen(ftp->pwd_tmp)) {
        if (chdir(ftp->path) < 0)
            return write_message(fd, "550 Failed to change directory.\r\n");
        change_directory(ftp);
    }
    return EXIT_SUCCESS;
}