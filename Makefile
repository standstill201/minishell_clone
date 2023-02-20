# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:03:12 by seokjyoo          #+#    #+#              #
#    Updated: 2023/02/20 20:55:11 by gychoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAG		=	-g#-Wall -Wextra -Werror

RM			=	rm -rf


SRC			=	./main.c \
				./parse/parse_data.c \
				./parse/parse_meta.c \
				./parse/parse_meta2.c \
				./parse/seperate_string.c \
				./parse/setting_quote.c \
				./parse/redi_process/set_here.c \
				./parse/redi_process/heredoc_input.c \
				./parse/redi_process/del_redi_read_here.c \
				./parse/final_parse/final_parse_lst.c \
				./parse/final_parse/final_parse.c \
				./error_handle/minishell_error.c \
				./error_handle/execute_error.c \
				./parse/redi_process/get_next_line.c \
				./execute/execute.c \
				./environ/environ.c \
				./environ/environ_utils.c \
				./builtin/ft_cd.c \

OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)

clean		:
				$(RM) $(OBJ_MAN) $(OBJ_BONUS) $(LIBFT) all bonus $(OBJ)

fclean		:	clean
				$(RM) $(NAME)
re			:
				$(MAKE) fclean
				$(MAKE) all

%.o			:	%.c
				$(CC) $(CFLAG) -c $< -o $@

$(NAME)		:	$(OBJ)
				cd LIBFT ; make ; cd ../
				$(CC) $(CFLAG) $(OBJ) ./LIBFT/libft.a -lreadline -o $(NAME)

.PHONY		:	all clean fclean re bonus
