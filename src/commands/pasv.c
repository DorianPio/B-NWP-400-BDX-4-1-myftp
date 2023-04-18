/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** pasv
*/

#include "../../include/socket.h"

in_addr_t get_ip(ftp_s *ftp)
{
    t_sockaddr adrs;
    socklen_t addrlen = sizeof(adrs);
    int result = getsockname(ftp->client, (struct sockaddr *)&adrs, &addrlen);

    if (result == -1) {
        printf("getsockname failed\n");
        return EXIT_FAILURE;
    }
    return inet_addr(inet_ntoa(adrs.sin_addr));
}

int this_port(ftp_s *ftp)
{
    t_sockaddr adrs;
    socklen_t addrlen = sizeof(adrs);
    int result = getsockname(ftp->client, (struct sockaddr *)&adrs, &addrlen);

    if (result == -1) {
        printf("getsockname failed\n");
        return EXIT_FAILURE;
    }
    return ntohs(adrs.sin_port);
}

char **get_uniqued_ip(char *actual)
{
    char **ip = malloc(sizeof(char *) * 5);

    ip[0] = strtok(actual, ".");
    ip[1] = strtok(NULL, ".");
    ip[2] = strtok(NULL, ".");
    ip[3] = strtok(NULL, ".");
    ip[4] = NULL;
    return ip;
}

int send_info(ftp_s *ftp, t_sockaddr adrs)
{
    socklen_t addrlen = sizeof(adrs);
    int result = getsockname(ftp->transmission_socket,
    (struct sockaddr *)&adrs, &addrlen);
    char **ip = get_uniqued_ip(inet_ntoa(adrs.sin_addr));
    char *str = get_info(ftp, ip);

    if (listen_t(ftp->transmission_socket, 1) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (result == -1)
        printf("getsockname failed\n");
    else {
        write_message(ftp->client, str);
        if (str)
            free(str);
    }
    ftp->mode = PASSIVE;
    ftp->transmission = accept_socket(ftp->transmission_socket);
    return EXIT_SUCCESS;
}

int pasv_cmd(ftp_s *ftp)
{
    t_sockaddr adrs;

    if (!ftp->connection)
        write_message(ftp->client, LOGIN);
    else {
        close_with_mode(ftp);
        ftp->transmission_socket = create_socket();
        adrs.sin_family = AF_INET;
        adrs.sin_addr.s_addr = get_ip(ftp);
        ftp->transmission_port = this_port(ftp) + 1;
        adrs.sin_port = htons(ftp->transmission_port);
        for (; bind(ftp->transmission_socket, (const struct sockaddr *)&adrs,
                sizeof(adrs)) == -1 && ftp->transmission_port < 65536;
                ftp->transmission_port++)
            adrs.sin_port = htons(ftp->transmission_port);
        if (ftp->transmission_port > 65536 ||
        send_info(ftp, adrs) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}