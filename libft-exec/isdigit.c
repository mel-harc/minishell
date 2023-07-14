/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:28:43 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/11 15:44:00 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

char	*_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*_str_varibale(char *str)
{
	int		i;

	i = 0;
	if (parse_export(str))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	if (str[i - 1] == '+')
	{
		g_exit_status = -42;
		i = i - 1;
	}
	return (find_variable(str, i));
}

char	*_strchr_value(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	if (*s == (char)c)
		s++;
	return ((char *)s);
}

void	create_new_variable(char *cmd, t_data *data)
{
	char	*variable;
	char	*value;
	t_env	*tmp;
	char	*save;

	variable = _str_varibale(cmd);
	value = _strchr_value(cmd, '=');
	if (searche(variable, data->ev))
	{
		if (g_exit_status == -42)
		{
			g_exit_status = 0;
			tmp = searche(variable, data->ev);
			save = tmp->value;
			tmp->value = _strjoin(tmp->value, value);
			free(save);
		}
		else
			replace(cmd, data);
	}
	else
		create_and_addback_env_node(&data->ev, variable, value);
	g_exit_status = 0;
	if (variable)
		free(variable);
}
