/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** server
*/

#include "socket.h"
#include <linux/limits.h>

static int init_ftp(ftp_s *ftp, int client, int socket, char *path)
{
    ftp->client = client;
    ftp->server = socket;
    ftp->end = false;
    ftp->connection = false;
    ftp->username = NULL;
    chdir(path);
    ftp->path = get_current_dir_name();
    ftp->mode = NONE;
    ftp->pwd_tmp = malloc(sizeof(char) * (PATH_MAX + 1));
    if (!ftp->pwd_tmp)
        return EXIT_FAILURE;
    ftp->pwd = ftp->pwd_tmp;
    memset(ftp->pwd_tmp, 0, PATH_MAX + 1);
}

int my_strlen(char *str)
{
    register int i = 0;

    for (; str && str[i]; i++);
    return i;
}

static int quit(ftp_s *ftp, char *cmd, int client)
{
    free_struct(ftp);
    if (cmd == NULL) {
        close(client);
        return EXIT_FAILURE;
    } else
        free(cmd);
    return EXIT_SUCCESS;
}

int receive_info(int socket, int client, char *path)
{
    char *cmd = NULL;
    ftp_s *ftp = malloc(sizeof(ftp_s));

    if (!ftp)
        return EXIT_FAILURE;
    if (init_ftp(ftp, client, socket, path) == EXIT_FAILURE)
        return EXIT_FAILURE;
    write_message(client, "220 Service ready for new user.\r\n");
    for (; !ftp->end && (cmd = command_prompt(client));cmd = NULL) {
        ftp->all_commands = str_to_wordarray(cmd);
        if ((ftp->all_commands == NULL || ftp->all_commands[0] == NULL) &&
        my_strlen(cmd) > 1)
            manage_null_command(ftp);
        if (manage_all_commands(ftp) == EXIT_QUIT)
            return EXIT_QUIT;
        free(cmd);
        free_tab(ftp->all_commands);
    }
    return quit(ftp, cmd, client);
}

int server_use(int socket, int client, char *path)
{
    int result = receive_info(socket, client, path);

    if (result == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    if (result == EXIT_QUIT) {
        return EXIT_QUIT;
    }
    if (close(socket) == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}