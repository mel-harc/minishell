/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:44:16 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/09 22:48:40 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **cmd, t_data *data)
{
	int		ret;

	if (cmd[1] && _strcmp(cmd[1], "-"))
		return (cd_dash(data));
	replace_old_pwd(data);
	if (!cmd[1] || _strcmp(cmd[1], "~"))
		ret = chdir("/Users/mel-harc");
	else
		ret = chdir(cmd[1]);
	if (ret == 0)
	{
		replace_pwd(data);
		return ;
	}
	else
	{
		g_exit_status = 1;
		_putstr_fd("cd: No such file or directory\n", 2);
	}
}

void	cd_dash(t_data *data)
{
	t_env	*node;
	t_env	*pwd;
	char	*save;
	int		ret;

	node = _is_exist(data, "OLDPWD");
	if (node)
	{
		ret = chdir(node->value);
		if (ret == 0)
		{
			printf("%s\n", node->value);
			save = node->value;
			pwd = _is_exist(data, "PWD");
			if (pwd)
			{
				node->value = _strdup(pwd->value);
				free(save);
			}
			return (replace_pwd(data));
		}
	}
	else
		return (error_cd());
}

void	replace_pwd(t_data *data)
{
	t_env	*node;
	char	*save;
	char	*str;

	node = _is_exist(data, "PWD");
	if (node)
	{
		save = node->value;
		str = getcwd(NULL, 0);
		if (!str)
		{
			_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
			_putstr_fd("cannot access parent directories: ", 2);
			_putstr_fd("No such file or directory\n", 2);
			str = _strjoin(save, "/..");
			node->value = str;
		}
		else
			node->value = str;
		free(save);
	}
}

void	replace_old_pwd(t_data *data)
{
	t_env	*node;
	char	*save;

	node = _is_exist(data, "OLDPWD");
	if (node)
	{
		save = node->value;
		node->value = getcwd(NULL, 0);
		free(save);
	}
	else
	{
		save = getcwd(NULL, 0);
		create_and_addback_env_node(&data->ev, "OLDPWD", save);
		free(save);
	}
}

t_env	*_is_exist(t_data *data, char *search)
{
	t_env	*tmp;

	tmp = data->ev;
	while (tmp)
	{
		if (_strcmp(search, tmp->variable))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
