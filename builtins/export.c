/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:33:05 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/14 08:42:10 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(char **cmd, t_data *data)
{
	if (!cmd[1])
		show_export(data->ev);
	else
		add_export(cmd, data);
	return ;
}

void	add_export(char **cmd, t_data *data)
{
	char	*variable;
	char	*value;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (_strnstr(cmd[i], "=", _strlen(cmd[i])))
			create_new_variable(cmd[i], data);
		else if (!_strnstr(cmd[i], "=", _strlen(cmd[i])))
		{
			variable = _str_varibale(cmd[i]);
			value = NULL;
			create_and_addback_env_node(&data->ev, variable, value);
			free(variable);
		}
	}
}

void	replace(char *str, t_data *data)
{
	t_env	*tmp;
	char	*save;
	char	*value;

	tmp = data->ev;
	while (tmp)
	{
		if (_strnstr(str, tmp->variable, _strlen(tmp->variable)))
		{
			save = tmp->value;
			value = _strchr_value(str, '=');
			tmp->value = ft_strdup(value);
			free(save);
			break ;
		}
		tmp = tmp->next;
	}
}

t_env	*searche(char *str, t_env *head)
{
	t_env	*tmp;

	tmp = head;
	if (!str)
		return (NULL);
	while (tmp)
	{
		if (_strnstr(str, tmp->variable, _strlen(tmp->variable)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	show_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (_strcmp(tmp->declare, "declare -x"))
		{
			printf("%s %s", tmp->declare, tmp->variable);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
}
