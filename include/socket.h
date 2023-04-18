/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** socket
*/

#ifndef SOCKET_H_
#define SOCKET_H_

# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define LIST "150 File status okay; about to open data connection.\r\n"
#define LOGIN "530 Please login with USER and PASS.\r\n"
#define CLOSE "Closing data connection.\n Requested file action"
#define CLOSE2 "successful (for example, file transfer or file abort).\n\r"

#define EXIT_SUCCESS 0
#define EXIT_QUIT 90
#define CLIENT_MAX 50

enum mode_transmission {
    PASSIVE,
    ACTIVE,
    NONE
};

typedef struct ftp_t {
    int client;
    int server;
    char *username;
    bool connection;
    bool end;
    char *pwd;
    char *pwd_tmp;
    char *path;
    enum mode_transmission mode;
    int transmission;
    int transmission_socket;
    int transmission_port;
    char **all_commands;
} ftp_s;

int ls_cmd(ftp_s *ftp);
int cwd_cmd(ftp_s *ftp);
int pwd_cmd(ftp_s *ftp);
int dele_cmd(ftp_s *ftp);
int help_cmd(ftp_s *ftp);
int list_cmd(ftp_s *ftp);
int pass_cmd(ftp_s *ftp);
int quit_cmd(ftp_s *ftp);
int pasv_cmd(ftp_s *ftp);
int noop_cmd(ftp_s *ftp);
int user_cmd(ftp_s *ftp);
int stor_cmd(ftp_s *ftp);
int cdup_cmd(ftp_s *ftp);
int port_cmd(ftp_s *ftp);
int retr_cmd(ftp_s *ftp);

extern int (*ptr_command[])(ftp_s *);
extern char *command_name[];

typedef struct sockaddr_in t_sockaddr;
typedef struct protoent t_protoent;

int create_socket();
int my_strlen(char *str);
void free_tab(char **tab);
char *get_next_line(int fd);
int stop_socket(int socket);
void free_struct(ftp_s *ftp);
int accept_socket(int socket);
char *command_prompt(int client);
void close_with_mode(ftp_s *ftp);
char *get_current_dir_name(void);
char **str_to_wordarray(char *str);
int manage_all_commands(ftp_s *ftp);
void manage_null_command(ftp_s *ftp);
char *get_info(ftp_s *ftp, char **ip);
int listen_t(int socket, int clients);
int start_socket(int socket, char *port);
int accept_clients(int socket, char *path);
int get_first(char *buf, int *i, int *point);
int write_message(int fd, const char *message);
int server_use(int socket, int client, char *path);

#endif /* !SOCKET_H_ */
