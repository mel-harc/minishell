# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 10:35:10 by houadou           #+#    #+#              #
#    Updated: 2023/07/11 15:59:40 by mel-harc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	minishell
HEADER			=	minishell.h
LIBFT			= 	libft/libft.a


CC 				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
# READLINE_INC	= 	-I/Users/houadou/homebrew/Cellar/readline/8.2.1/include
# READLINE_LIB	=	-L/Users/houadou/homebrew/Cellar/readline/8.2.1/lib -lreadline
READLINE_INC	= 	-I/Users/mel-harc/.brew/Cellar/readline/8.2.1/include
READLINE_LIB	=	-L/Users/mel-harc/.brew/Cellar/readline/8.2.1/lib -lreadline
RM 				= 	rm -f


SRC 			=   minishell.c parse/free_functions.c parse/lst_creation/env_lst_create.c \
					parse/token_creation/token_create.c parse/lst_creation/token_lst_create.c parse/token_creation/token_tools.c parse/token_creation/token_tools2.c \
					parse/token_check/check_tokens.c parse/token_check/check_tokens2.c parse/expand/parse_expande.c parse/expand/parse_expande2.c \
					parse/final_part/final_parse.c parse/free_functions2.c parse/final_part/final_parse_tools.c parse/final_part/final_parse_tools2.c parse/final_part/heredoc_tools.c \
					parse/lst_creation/command_lst_create.c parse/final_part/final_parse2.c \
					excution/excution.c excution/utls.c excution/function_help.c excution/fill_env.c excution/exit_status.c excution/exec_cmd.c\
					libft-exec/strnstr.c libft-exec/split.c  libft-exec/substr.c libft-exec/strtrim.c \
					libft-exec/getstr.c libft-exec/strjoin.c libft-exec/atoi.c libft-exec/isdigit.c libft-exec/putstr_fd.c \
					builtins/builtins_main.c builtins/echo.c builtins/cd.c builtins/exit.c builtins/export.c builtins/env.c builtins/pwd.c  builtins/unset.c parse/signals.c \


OBJ				= 	$(SRC:.c=.o)


all				: 	$(NAME)


$(NAME)			: 	$(OBJ) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(READLINE_INC) $(READLINE_LIB) $(LIBFT) $(OBJ) -o $(NAME)


%.o 			:	 %.c $(HEADER)
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@


$(LIBFT)		:
	make bonus -C libft


clean			:
	$(RM) $(OBJ)
	make clean -C libft


fclean			: 	clean
	$(RM) $(NAME)
	make fclean -C libft


re 				: 	fclean all

.PHONY: all clean fclean re
