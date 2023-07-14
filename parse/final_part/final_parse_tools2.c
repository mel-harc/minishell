/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse_tools2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:02 by houadou           #+#    #+#             */
/*   Updated: 2023/07/08 18:00:59 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	initiate_heredoc(char **file)
{
	int		fd;

	(*file) = "/tmp/.tmp";
	fd = open((*file), O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

char	*is_valid_env2(char *str, int *i)
{
	char	*tmp;
	int		j;
	int		after_dollar;

	j = 0;
	after_dollar = *i + 1;
	while (str[++(*i)])
	{
		if (str[*i] == '$' || str[*i] == '\"' || str[*i] == '\'' || \
		ft_strchr(WHITE_SPACES, str[*i]) || ft_strchr(SPECIAL_CHAR, str[*i]))
			break ;
		j++;
	}
	if (j == 0)
		return (NULL);
	tmp = ft_substr(str, after_dollar, j);
	return (tmp);
}

char	*get_env_2(char *str, t_data *data)
{
	t_env	*env;
	char	*tmp;

	if (str[0] == '?' && str[1] == '\0')
		return (free(str), ft_itoa(g_exit_status));
	if (str[0] == '?' && str[1] != '\0' && str[2] != '$')
	{
		tmp = join_strings(ft_itoa(g_exit_status), str + 1, 1);
		free(str);
		return (tmp);
	}
	env = data->ev;
	while (env)
	{
		if (ft_strcmp(env->variable, str) == 0)
		{
			free(str);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free(str);
	return (NULL);
}

void	expande_merge(char **line, char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	if ((*line)[i] != '\0')
		tmp = ft_substr((*line), i, ft_strlen(*line));
	free(*line);
	(*line) = join_strings(str, tmp, 0);
}

int	here_doc(t_data *data, t_token **tokens)
{
	int		fd;
	char	*file;
	char	*line;

	fd = initiate_heredoc(&file);
	if (fd == -1)
		return (perror("minishell$>"), -1);
	while (1)
	{
		signal(SIGINT, here_doc_sigint);
		line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, (*tokens)->content) == 0)
			break ;
		if (finally_is_valid((*tokens)->type, 7))
			line = variable_or_not(data, line, 0);
		ft_putendl_fd(line, fd);
		free(line);
	}
	dup2(data->std_int, 0);
	return (free(line), close(fd), get_here_doc(file));
}
