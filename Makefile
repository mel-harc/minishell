# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 17:59:51 by mel-harc          #+#    #+#              #
#    Updated: 2023/06/04 22:23:01 by mel-harc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = minishell.h

CC = cc

RM = rm -rf

FLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRC = excution/excution.c  minishell.c excution/fill_env.c \
		libft/strnstr.c libft/split.c  libft/substr.c libft/strtrim.c \
		libft/getstr.c libft/strjoin.c excution/fill_cmds.c  excution/utls.c \
		excution/function_help.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(OBJ) $(FLAGS) -o  $(NAME) -lreadline

clean : 
	$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re