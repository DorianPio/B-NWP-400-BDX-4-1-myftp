##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## create
##

SRC	=	src/main.c						\
		src/clients.c					\
		src/close_with_mode.c			\
		src/command.c					\
		src/get_info.c					\
		src/create_socket.c				\
		src/manage_command.c			\
		src/null_command.c				\
		src/other.c						\
		src/server.c					\
		src/socket.c					\
		src/commands/delete.c			\
		src/commands/help.c				\
		src/commands/list.c				\
		src/commands/noop.c				\
		src/commands/port.c				\
		src/commands/pass.c				\
		src/commands/pasv.c				\
		src/commands/pwd.c				\
		src/commands/quit.c				\
		src/commands/stor.c				\
		src/commands/retr.c				\
		src/commands/user.c				\
		src/commands/cwd.c				\
		src/commands/cdup.c				\
		src/commands/ls.c				\
		src/commands/port_extend.c		\
		get_next_line/get_next_line.c	\
		src/write_for_the_client.c

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

CPPFLAGS	=	-I./include -g


all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -g
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f $(OBJ)

re:	fclean all

