/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:16:40 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/08 13:22:13 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(char **cmd)
{
	if (_strcmp(cmd[0], "echo"))
		return (1);
	else if (_strcmp(cmd[0], "echo "))
		return (1);
	else if (_strcmp(cmd[0], "cd"))
		return (1);
	else if (_strcmp(cmd[0], "export"))
		return (1);
	else if (_strcmp(cmd[0], "pwd"))
		return (1);
	else if (_strcmp(cmd[0], "unset"))
		return (1);
	else if (_strcmp(cmd[0], "env"))
		return (1);
	else if (_strcmp(cmd[0], "exit"))
		return (1);
	else
		return (0);
}

int	built_main(char **cmd)
{
	if (_strcmp(cmd[0], "cd"))
		return (1);
	else if (_strcmp(cmd[0], "pwd"))
		return (1);
	else if (_strcmp(cmd[0], "unset"))
		return (1);
	else if (_strcmp(cmd[0], "export"))
		return (1);
	else if (_strcmp(cmd[0], "env"))
		return (1);
	else if (_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

void	run_builtins(char **cmd, t_data *data)
{
	if (_strcmp(cmd[0], "echo"))
		echo(cmd);
	else if (_strcmp(cmd[0], "cd"))
		cd(cmd, data);
	else if (_strcmp(cmd[0], "exit"))
		eexit(cmd);
	else if (_strcmp(cmd[0], "export"))
		export(cmd, data);
	else if (_strcmp(cmd[0], "env"))
		show_env(data->ev);
	else if (_strcmp(cmd[0], "pwd"))
		show_pwd(data);
	else if (_strcmp(cmd[0], "unset"))
		unset(cmd, data);
	else if (_strcmp(cmd[0], "echo "))
	{
		write(1, "\n", 1);
		exit(0);
	}
}
