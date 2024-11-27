/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:19:48 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/08 21:19:24 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_cmd(char *cmd, t_env *env)
{
	int		i;
	char	*str;
	char	*ncmd;
	char	**paths;

	i = 0;
	if (_strnstr(cmd, "/", _strlen(cmd)))
		return (cmd);
	paths = _split(get_path(env), ':');
	if (!paths)
		return (NULL);
	if (path_cmd(cmd))
		return (cmd);
	ncmd = _strjoin("/", cmd);
	if (!ncmd)
		exit(1);
	while (paths[++i])
	{
		str = _strjoin(paths[i], ncmd);
		if (!access(str, F_OK | X_OK))
			return (free_paths(paths), free(ncmd), str);
		free(str);
	}
	return (free(ncmd), free_paths(paths), NULL);
}

int	path_cmd(char *cmd)
{
	if (!access(cmd, F_OK | X_OK))
		return (1);
	else
		return (0);
}

char	*get_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (_strnstr(tmp->variable, "PATH", 4))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	size_lst(t_command *head)
{
	int			i;
	t_command	*tmp;

	i = -1;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	**alloc_fds(t_command *head)
{
	int	**table;
	int	i;
	int	cnt;

	cnt = size_lst(head);
	table = (int **)malloc(sizeof(int *) * (cnt + 1));
	if (!table)
		return (NULL);
	i = -1;
	while (++i < cnt)
	{
		table[i] = malloc(sizeof(int) * 2);
		if (!table[i])
			return (NULL);
	}
	table[i] = NULL;
	return (table);
}
