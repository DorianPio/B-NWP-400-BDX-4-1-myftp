/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** main
*/

#include "socket.h"
#include <signal.h>

int (*ptr_command[])(ftp_s *) ={&user_cmd,
                                &pass_cmd,
                                &quit_cmd,
                                &dele_cmd,
                                &cwd_cmd,
                                &cdup_cmd,
                                &pwd_cmd,
                                &pasv_cmd,
                                &port_cmd,
                                &help_cmd,
                                &noop_cmd,
                                &retr_cmd,
                                &stor_cmd,
                                &list_cmd,
                                &ls_cmd,
                                NULL};

char *command_name[] =  {"USER",
                        "PASS",
                        "QUIT",
                        "DELE",
                        "CWD",
                        "CDUP",
                        "PWD",
                        "PASV",
                        "PORT",
                        "HELP",
                        "NOOP",
                        "RETR",
                        "STOR",
                        "LIST",
                        "LS",
                        NULL};

static void help_displays()
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport  is the port number on which the server socket listens\n");
    printf("\tpath  is the path to the home directory"
    "for the Anonymous user\n");
}

static int testpath(char *path)
{
    if (chdir(path) == -1) {
        fprintf(stderr, "Invalid path: %s\n", path);
        return EXIT_FAILURE;
    }
}

static void welcome_message(char **av)
{
    printf("Welcome to the server on the port %s\nAt the PATH: %s\n",
    av[1], av[2]);
}

static void sig_handler(int signal)
{
    if (signal == SIGINT) {
        exit(0);
    }
}

int main(int ac, char **av)
{
    int socket = 0;

    signal(SIGINT, sig_handler);
    if (ac != 3) {
        help_displays();
        return EXIT_SUCCESS;
    } else if (strcmp(av[1], "-help") == 0) {
        help_displays();
        return EXIT_SUCCESS;
    }
    if (testpath(av[2]) == EXIT_FAILURE) { return 84;}
    socket = create_socket();
    if (socket == EXIT_FAILURE)
        return 84;
    if (start_socket(socket, av[1]) == EXIT_FAILURE) { return 84;}
    welcome_message(av);
    if (listen_t(socket, CLIENT_MAX) == EXIT_FAILURE) { return 84;}
    if (accept_clients(socket, av[2]) == EXIT_FAILURE) { return 84;}
}
