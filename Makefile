# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhervy <dhervy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/18 01:28:07 by dhervy            #+#    #+#              #
#    Updated: 2017/04/21 22:14:48 by dhervy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = clang
CFLAGS = -Wall -Werror -Wextra -g

CPATH = srcs/
CFILES = \
	main.c \
	ft_init_term.c \
	get_line.c \
	get_line2.c \
	get_line3.c \
	get_key.c \
	get_key2.c \
	realloc.c \
	history.c \
	moove_cursor.c \
	moove_cursor2.c \
	moove_cursor3.c \
	moove_cursor4.c \
	parser.c \
	parser2.c \
	parser3.c \
	get_parser.c \
	get_parser2.c \
	get_parser3.c \
	token.c \
	token2.c \
	lexer.c \
	exec.c \
	exec2.c \
	exec3.c \
	exec4.c \
	arbre.c \
	arbre2.c \
	autocomplet.c \
	autocomplet2.c \
	autocomplet3.c \
	autocomplet4.c \
	heredoc.c \
	echo.c \
	exit.c \
	cd.c \
	env.c \
	env1.c \
	env2.c \
	env3.c \
	envcopy.c \
	checkvar.c \
	free.c \
	tool.c \
	tool2.c

OPATH = obj/
OFILES = $(CFILES:.c=.o)
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling \"$(NAME)\"..."
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -Llibft  -ltermcap -lft -o $(NAME)
	@echo "Successful compilation!\n---"

$(OPATH)%.o: $(CPATH)%.c
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -I includes -I libft -c -o $@ $<

clean:
	@echo "Deleting the directory /obj..."
	make -C libft clean
	@rm -f $(OBJ)
	@echo "Deletion complete !"

fclean: clean
	@echo "Deleting binary "$(NAME)"..."
	make -C libft fclean
	@rm -f $(NAME)
	@echo "Deletion complete !"/

re: fclean all
