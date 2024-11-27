/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:33:54 by houadou           #+#    #+#             */
/*   Updated: 2023/07/08 18:30:51 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc_sigint(int sig)
{
	(void)sig;
	close(0);
	g_exit_status = 1;
}

char	*trim(char **line, int flag)
{
	char	*tmp;

	tmp = ft_strdup(*line);
	free(*line);
	if (flag == 1)
		*line = ft_strtrim(tmp, " \t\n");
	else
		*line = ft_strtrim(tmp, "\n");
	free(tmp);
	return (*line);
}

char	*variable_or_not(t_data *data, char *line, int i)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0')
		{
			str = ft_strdup(line);
			tmp = ft_substr(str, 0, i);
			tmp2 = is_valid_env2(str, &i);
			if (!tmp2)
				return (free(str), free(tmp), free(tmp2), NULL);
			free(str);
			str = join_strings(tmp, get_env_2(tmp2, data), 0);
			expande_merge(&line, str, i);
			i = -1;
		}
		i++;
	}
	return (line);
}

int	get_here_doc(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("minishell$>"), -1);
	return (fd);
}
