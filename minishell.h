/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:29:26 by houadou           #+#    #+#             */
/*   Updated: 2023/07/11 14:54:31 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <inttypes.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define WHITE_SPACES " \t\n"
# define NOT_VALID_WORD "\'\"\t\n ><$|"
# define SPECIAL_CHAR "!~|@%^*{}$[].-+=/#"
# define ERROR_PIPES "minishell$> syntax error near unexpected token `|'\n"
# define ERROR_REDIR "minishell$> syntax error near unexpected \
	token `newline'\n"

extern int	g_exit_status;

typedef enum s_tokens_type{
	PIPE,
	INPUT_RED,
	OUTPUT_RED,
	WHITE_SPACE,
	HEREDOC,
	APPEND,
	DOLLAR,
	DB_QUOTE_STRING,
	SG_QUOTE_STRING,
	VARIABLE,
	VALID_WORD,
	SIMPLE_DELIM,
	QUOTED_DELIM,
	HEAD,
}	t_tokens_type;

typedef struct s_token
{
	struct s_token			*next;
	t_tokens_type			type;
	char					*content;
	struct s_token			*prev;
}	t_token;

typedef struct s_enviroment
{
	struct s_enviroment	*next;
	char				*variable;
	char				*value;
	char				*declare;
	struct s_enviroment	*prev;
}	t_env;

typedef struct s_data
{
	t_env	*ev;
	int		db_quotes;
	int		sg_quotes;
	int		size_of_list;
	int		input;
	int		output;
	int		std_out;
	int		std_int;
}	t_data;

typedef struct s_command
{
	struct s_command	*next;
	char				**command;
	int					output;
	int					input;
	struct s_command	*prev;
}	t_command;

// Function on directory excution
void		execmds(t_command **cmd, t_data *data);
void		mlt_cmds(t_command **cmds, t_data *data);
void		loop_cmds(t_command *tmp_cmd, int **pipefd, t_data *data);
char		*check_cmd(char *cmd, t_env *env);
void		one_cmd(t_command **cmd, t_data *data);
void		first_cmd(t_command *cmd, int *pipe, t_data *data);
void		last_cmd(t_command *cmd, t_data *data, int *pipefd);
void		middle_cmd(t_command *cmd, t_data *data, int *old_pipe, \
			int *new_pipe);
void		_exec(t_command *cmd, t_data *data);
int			size_lst(t_command *head);
int			**alloc_fds(t_command *head);
int			check_builtins(char **cmd);
void		run_builtins(char **cmd, t_data *data);
int			built_main(char **cmd);
void		echo(char **cmd);
void		cd(char **cmd, t_data *data);
char		*search_chr(const char *s, int c);
void		eexit(char **cmd);
void		put_error(int flag, char *arg, int nbr);
void		status_of_exit(int status);
void		free_fd(int **array_fd);
char		**_env(t_env *env);
int			size_of_var(t_env *env);
char		*get_path(t_env *env);
int			path_cmd(char *cmd);
void		_redirect(t_command *cmd);
void		update_exit_status(pid_t pid);
void		export(char **cmd, t_data *data);
void		add_export(char **cmd, t_data *data);
void		show_export(t_env *env);
void		show_env(t_env *env);
void		show_pwd(t_data *data);
void		unset(char **cmd, t_data *data);
void		free_node(t_env *node);
void		loop_for_node(char *cmd, t_data *data);
t_env		*searche(char *str, t_env *head);
void		replace(char *str, t_data *data);
void		create_new_variable(char *cmd, t_data *data);
char		*find_variable(char *str, int i);
int			parse_export(char *str);
void		exec_one_cmd(t_command **cmd, t_data *data);
void		exec_midle_cmd(t_command *cmd, t_data *data, int *new, int *old);
void		free_paths(char **str);
void		replace_pwd(t_data *data);
void		replace_old_pwd(t_data *data);
t_env		*_is_exist(t_data *data, char *search);
void		signal_shell_level(t_data *data);
void		_set_path(t_data *data);
void		cd_dash(t_data *data);
void		error_cd(void);

// Function on directory libft
char		*_strnstr(const char *haystack, const char *needle, size_t len);
char		*_substr(const char *s, unsigned int start, size_t len);
char		*_strjoin(const char *s1, const char *s2);
size_t		_strlen(const char *s);
char		*_strtrim(char const *s1, char const *set);
char		**_split(const char *s, char c);
char		*getstr(char *src);
int			_atoi(const char *str);
int			_isdigit(int c);
char		*_strchr(const char *s, int c);
char		*_str_varibale(char *str);
char		*_strchr_value(const char *s, int c);
void		_putstr_fd(char *s, int fd);
int			_isalpha(int c);
int			_strcmp(const char *s1, const char *s2);
char		*_strdup(const char *str);
size_t		_strlcpy(char *dst, const char *src, size_t dstsize);
char		*_itoa(int n);
void		set_error(char *path, t_command *cmd);
int			parse_arg_unset(char *arg);

/* Check environment and create list */

void		create_and_addback_env_node(t_env **head, char *variable, \
			char *value);
t_env		*create_new_env_node(char *variable, char *value);

/* Tokens */

t_token		*create_new_tok_node(char *content, int token_type);
void		create_addback_tok_node(t_token **head, char *content, \
			int token_type);
void		start_token(char *line, t_data *data);
int			check_quotes(char *line, t_data *data);
void		tokens_manage(char *line, int *index, t_token **tokens);
int			check_conditions(char *line, int i);
char		*manage_string(int flag, char *s1, char *s2, char character);
char		*join_strings(char *s1, char *s2, int flag);
void		token_variable_manage(char *line, t_token **tokens, int *index);
void		token_word_manage(char *line, t_token **tokens, int *index);
int			check_tokens(t_token **tokens);
int			check_redirection(t_token **tokens);
void		start_expand(t_token **tokens, t_data *data);
void		quoted_expand(t_token **tokens, t_data *data);
void		merge_quoted_string(t_token **tokens);

/* Creation of command list */

t_command	*create_new_command(int output, int input);
void		create_addback_cmd(t_command **head, int output, int input, \
			char **cmd);
char		**cmd_creation(char **cmd);
int			start_final_parse(t_token **tokens, t_data *data);
int			finally_is_valid(int type, int flag);
void		redirection_manage(t_data *data, t_token **tokens);
int			here_doc(t_data *data, t_token **tokens);
char		*variable_or_not(t_data *data, char *line, int i);
char		*is_valid_env2(char *str, int *i);
char		*get_env_2(char *str, t_data *data);
void		expande_merge(char **line, char *str, int i);
char		*trim(char **line, int flag);
int			get_here_doc(char *file);
void		here_doc_sigint(int sig);
void		signal_handler(void);
void		sigint_handler(int sig);

/* Free functions */

void		free_tab(char **tab);
void		free_tokens(t_token **tokens);
t_token		*current_node_erase(t_token *tok);
t_token		*next_node_erase(t_token *tok);
void		free_commands(t_command **cmd);
void		free_env(t_env **env);

#endif
