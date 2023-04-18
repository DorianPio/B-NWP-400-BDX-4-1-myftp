/*
** EPITECH PROJECT, 2021
** B-NWP-400-BDX-4-1-myftp-dorian.pio
** File description:
** port
*/

#include "socket.h"
#include <linux/limits.h>

static int linked_socket(int socket, int port, char *ip)
{
    t_sockaddr addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    if (connect(socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect()");
        close(socket);
        return 84;
    }
    return EXIT_SUCCESS;
}

static char *get_ip(char *ip)
{
    char *ip_res = malloc(sizeof(char) * 17);
    int point = 0;
    int i = 0;

    memset(ip, 0, 17);
    for (; ip[i] && i < 17 && point < 4; i++) {
        if (ip[i] == ',' || ip[i] == '.') {
            if (point < 3)
                ip_res[i] = '.';
            ++point;
        } else if (ip[i] > '0' && ip[i] <= '9')
            ip_res[i] = ip[i];
        else
            return NULL;
    }
    return ip_res;
}

static int close_port(ftp_s *ftp, char *ip)
{
    if (linked_socket(ftp->transmission, ftp->transmission_port, ip) == 84) {
        free(ip);
        write_message(ftp->client, "425 Cannot connect to the port.\r\n");
        return EXIT_FAILURE;
    }
    free(ip);
    ftp->mode = ACTIVE;
    write_message(ftp->client, "200 Command okay.\r\n");
}

static int get_port(char *port)
{
    int point = 0;
    int first = 0;
    int i = 0;
    int point2 = 4;
    int second = 0;

    if (!port)
        return -1;
    for (; port[i] && point < 4; i++) {
        if (port[i] == ',' || port[i] == '.')
            point += 1;
    }
    first = get_first(port, &i, &point);
    second = get_first(port, &i, &point2);
    if (point < 5 || point2 > 4)
        return EXIT_FAILURE;
    return 256 * first + second;
}

int port_cmd(ftp_s *ftp)
{
    char *ip = get_ip(ftp->all_commands[1]);
    int fd = ftp->client;

    if (!ftp->connection)
        write_message(fd, "530 Please login with USER and PASS.\r\n");
    else {
        close_with_mode(ftp);
        if (ip == NULL)
            return write_message(fd, "501 Bad IP address passed.\r\n");
        ftp->transmission_port = get_port(ftp->all_commands[1]);
        if (ftp->transmission_port < 0) {
            free(ip);
            return write_message(fd, "501 Bad IP address passed.\r\n");
        }
        ftp->transmission_port = create_socket();
        return close_port(ftp, ip);
    }
    return EXIT_SUCCESS;
}