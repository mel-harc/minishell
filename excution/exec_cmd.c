/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:32:49 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/10 21:14:58 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_one_cmd(t_command **cmd, t_data *data)
{
	if (_strcmp((*cmd)->command[0], "./minishell"))
		signal_shell_level(data);
	signal(SIGQUIT, SIG_DFL);
	_exec((*cmd), data);
}

void	exec_midle_cmd(t_command *cmd, t_data *data, int *new, int *old)
{
	if (_strcmp(cmd->command[0], "./minishell"))
		signal_shell_level(data);
	signal(SIGQUIT, SIG_DFL);
	close(new[0]);
	dup2(old[0], 0);
	dup2(new[1], 1);
	close(old[0]);
	close(new[1]);
	if (cmd->input != -8 || cmd->output != -8)
		_redirect(cmd);
	if (check_builtins(cmd->command))
	{
		run_builtins(cmd->command, data);
		exit(0);
	}
	_exec(cmd, data);
}

void	signal_shell_level(t_data *data)
{
	t_env	*node;
	char	*save;
	int		level;

	signal(SIGINT, sigint_handler);
	node = _is_exist(data, "SHLVL");
	if (node)
	{
		save = node->value;
		level = _atoi(save) + 1;
		node->value = ft_itoa(level);
		free(save);
	}
}

void	set_error(char *path, t_command *cmd)
{
	free(path);
	if (access(cmd->command[0], F_OK))
	{
		_putstr_fd("minishell$: command not found\n", 2);
		exit(127);
	}
	else if (access(cmd->command[0], X_OK))
	{
		_putstr_fd("minishell$: Permission denied\n", 2);
		exit(126);
	}
	else
	{
		_putstr_fd("minishell$: error execve\n", 2);
		exit(1);
	}
}
