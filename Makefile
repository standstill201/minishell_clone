# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:03:12 by seokjyoo          #+#    #+#              #
#    Updated: 2023/02/21 14:33:31 by gychoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g
RM = rm -rf

LFTDIR = ./LIBFT/
LFTLIB = -L$(LFTDIR) -lft
LIBFT = $(LFTDIR)libft.a

READLINE = -lreadline

SRC = ./main.c \
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
	  ./builtin/ft_cd.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LFTLIB) $(READLINE) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LFTDIR)

clean:
	$(MAKE) -C $(LFTDIR) clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re : fclean
	$(MAKE) all

.PHONY:	all clean fclean re
