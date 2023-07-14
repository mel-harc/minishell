/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:34:48 by houadou           #+#    #+#             */
/*   Updated: 2023/06/15 14:19:24 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_commands(t_command **s_command)
{
	t_command	*temp;

	while (*s_command)
	{
		temp = *s_command;
		*s_command = (*s_command)->next;
		free_tab(temp->command);
		free(temp);
		temp = NULL;
	}
	*s_command = NULL;
}

void	free_env(t_env **ev)
{
	t_env	*tmp;

	while (*ev)
	{
		tmp = *ev;
		*ev = (*ev)->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp->declare);
		free(tmp);
	}
}
