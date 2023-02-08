# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seokjyoo <seokjyoo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:03:12 by seokjyoo          #+#    #+#              #
#    Updated: 2023/01/30 17:30:09 by seokjyoo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAG		=	#-Wall -Wextra -Werror

RM			=	rm -rf


SRC			=	./main/main.c \
				./parse/parse_data.c \
				./error_handle/sj_error.c

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
