/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** command
*/

#include "socket.h"

static char **str_to_wordarray2(char **result, char *str)
{
    int i2 = 0;
    int i3 = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            result[i2][i3] = '\0';
            if (result[i2][i3 - 1] == '\n')
                result[i2][i3 - 2] = '\0';
            i2++;
            i3 = 0;
            i++;
        }
        result[i2][i3] = str[i];
        i3++;
    }
    result[i2][i3] = '\0';
    result[i2 + 1] = NULL;
    if (result[i2][i3 - 1] == '\n')
        result[i2][i3 - 2] = '\0';
    return result;
}

char **str_to_wordarray(char *str)
{
    int nb_spaces = 0;
    char **result = NULL;

    if (str == NULL)
        return NULL;
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ')
            ++nb_spaces;
    }
    result = malloc(sizeof(char *) * nb_spaces);
    for (int i = 0; i < nb_spaces + 1; i++) {
        result[i] = malloc(sizeof(char) * strlen(str));
    }
    return str_to_wordarray2(result, str);
}

char *command_prompt(int client)
{
    char *command = get_next_line(client);

    return command == NULL ? NULL : command;
}