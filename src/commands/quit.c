/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** quit
*/

#include "socket.h"
#include <signal.h>

int quit_cmd(ftp_s *ftp)
{
    pid_t pid = getppid();
    pid_t pid2 = getpid();

    printf("Parent: %d\nChild: %d\n", pid, pid2);
    write_message(ftp->client, "221 Service closing control connection.\r\n");
    ftp->end = true;
    if (shutdown(ftp->client, 2) < 0) {
        write_message(ftp->server, "bite");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
