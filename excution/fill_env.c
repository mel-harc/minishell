/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:34:31 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/22 18:58:23 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	copy_envp(data, envp);	
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			data->path = ft_split(ft_strtrim(envp[i], "PATH="), ':');
			if (!data->path)
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
	printf("%d\n", j);
	return (j);
}

void	copy_envp(t_data *data, char **envp)
{
	int	i;

	data->head_envp = malloc(sizeof(t_envp));
	if (!data->head_envp)
		return ;
	while (envp[i++])
	{
		
	}
}