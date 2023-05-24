/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:59:46 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/24 22:26:15 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <libc.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
typedef	struct s_envp
{
	char			*str;
	struct s_envp	*next;
}	t_envp;

typedef struct s_data
{
	char	**paths;
	t_envp	*head_envp;
}	t_data;

// Function on directory excution
void	cmd1(char *cmd, char **env);
void	execmds(char *cmd, char **paths, char **envp);
void	fill_env(char **envp, t_data *data);
size_t	cntlen(char **envp);
void	copy_envp(t_data *data, char **envp);
t_envp	*lst_new(char *envp);
int		lst_add(t_data *data, t_envp *new_node);
char	*check_cmd(char *cmd, char **paths);



// Function on directory libft
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *s, char c);
char	*getstr(char *src);

#endif