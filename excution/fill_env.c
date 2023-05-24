/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:34:31 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/24 18:12:56 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	data->head_envp = NULL;
	copy_envp(data, envp);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->paths = ft_split(ft_strtrim(envp[i], "PATH="), ':');
			if (!data->paths)
				return ;
			break ;
		}
		i++;
	}
	return ;
}

size_t	cntlen(char **envp)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i++])
		j++;
	j++;
	return (j);
}

void	copy_envp(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		if (lst_add(data, lst_new(envp[i++])))
			return ;
}

int	lst_add(t_data *data, t_envp *new_node)
{
	t_envp	*head;

	head = NULL;
	if (!new_node)
		return (1);
	if (!data->head_envp)
		data->head_envp = new_node;
	else
	{
		head = data->head_envp;
		while (head->next)
			head = head->next;
		head->next = new_node;
	}
	return (0);
}

t_envp	*lst_new(char *envp)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->str = getstr(envp);
	node->next = NULL;
	return (node);
}