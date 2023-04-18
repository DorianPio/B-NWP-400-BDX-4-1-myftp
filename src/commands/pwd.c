/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** pwd
*/

#include "socket.h"
#include <linux/limits.h>

int pwd_cmd(ftp_s *ftp)
{
    char *str = malloc(sizeof(char) * PATH_MAX + 9);

    if (!ftp->all_commands || !ftp->connection)
        write_message(ftp->client, LOGIN);
    else {
        memset(ftp->pwd_tmp, 0, PATH_MAX);
        getcwd(ftp->pwd_tmp, PATH_MAX);
        sprintf(str, "257 \"%s\"created.\r\n", my_strlen(ftp->pwd_tmp) > 0 ?
        ftp->pwd_tmp : "/");
        write_message(ftp->client, str);
    }
    free(str);
    return EXIT_SUCCESS;
}