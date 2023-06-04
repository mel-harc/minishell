/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:19:48 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/04 18:59:02 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_cmd(char *cmd, char **paths)
{
	int		i;
	char	*str;
	char	*ncmd;

	i = 0;
	ncmd = ft_strjoin("/", cmd);
	if (!ncmd)
		return (NULL);
	while (paths[++i])
	{
		str = ft_strjoin(paths[i], ncmd);
		if (!str)
			return (NULL);
		if (!access(str, F_OK | X_OK))
			return (str);
		free(str);
	}
	free(ncmd);
	return (NULL);
}

int	size_lst(t_list_cmds *head)
{
	int			i;
	t_list_cmds	*tmp;

	i = -1;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	**alloc_fds(t_list_cmds *head)
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
