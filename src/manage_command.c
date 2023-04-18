/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** manage_command
*/

#include "socket.h"

int manage_all_commands(ftp_s *ftp)
{
    char *denied_permissions = "530 Permission denied.\r\n";
    char *commanddoesntexist = "500 Unknown command.\r\n";

    for (int i = 0; i < 15; i++) {
            if (ptr_command[i] && strncasecmp(command_name[i],
            ftp->all_commands[0], strlen(command_name[i])) == 0) {
                return ptr_command[i](ftp);
            }
    }
    if (!ftp->connection && strlen(ftp->all_commands[0]) > 0)
        write(ftp->client, denied_permissions, strlen(denied_permissions));
    write(ftp->client, commanddoesntexist, strlen(commanddoesntexist));
    return EXIT_SUCCESS;
}
