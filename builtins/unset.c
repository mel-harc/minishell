/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:44:17 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/11 15:44:36 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **cmd, t_data *data)
{
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (parse_arg_unset(cmd[i]))
			break ;
		loop_for_node(cmd[i], data);
	}
}

int	parse_arg_unset(char *arg)
{
	int	i;

	i = 0;
	if (_isalpha(arg[i]))
	{
		g_exit_status = 1;
		_putstr_fd("minishell$: not a valid identifier\n", 2);
		return (1);
	}
	while (arg[++i])
	{
		if (_strchr("!=#$%&'/-+()*,.?@[]\{^|}~", arg[i]))
		{
			g_exit_status = 1;
			_putstr_fd("minishell$: not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}

void	loop_for_node(char *cmd, t_data *data)
{
	t_env	*tmp;

	tmp = data->ev;
	while (tmp)
	{
		if (_strcmp(cmd, tmp->variable))
		{
			if (!tmp->prev)
			{
				data->ev = tmp->next;
				tmp->next->prev = NULL;
			}
			else if (!tmp->next)
				tmp->prev->next = NULL;
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			free_node(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	free_node(t_env *node)
{
	free(node->declare);
	free(node->value);
	free(node->variable);
	free(node);
}
