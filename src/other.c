/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** other
*/

#include "socket.h"

void free_struct(ftp_s *ftp)
{
    if (ftp->path)
        free(ftp->path);
    if (ftp->pwd_tmp)
        free(ftp->pwd_tmp);
    if (ftp->username)
        free(ftp->username);
}

void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}