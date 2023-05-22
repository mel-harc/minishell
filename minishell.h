/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:59:46 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/22 18:58:46 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**env;
	char	**path;
	char	*head_envp;
}	t_data;

typedef	struct s_envp
{
	char	*str;
}	t_envp;


// Function on directory excution
void	cmd1(char *cmd, char **env);
void	execmds(char *cmd, char **env);
void	fill_env(char **envp, t_data *data);
size_t	cntlen(char **envp);
void	copy_envp(t_data *data, char **envp);

// Function on directory libft
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strcpy(char *dst, char *src);
char	**ft_split(const char *s, char c);

#endif