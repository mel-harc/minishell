/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:18:16 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/11 11:11:16 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_command **cmd, t_data *data)
{
	int			pid;

	if (built_main((*cmd)->command))
		run_builtins((*cmd)->command, data);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid != 0)
			update_exit_status(pid);
		if (pid == 0)
		{
			if ((*cmd)->input != -8 || (*cmd)->output != -8)
				_redirect((*cmd));
			if (check_builtins((*cmd)->command))
			{
				run_builtins((*cmd)->command, data);
				exit(0);
			}
			exec_one_cmd(cmd, data);
		}	
	}
}

void	first_cmd(t_command *cmd, int *pipe, t_data *data)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (_strcmp(cmd->command[0], "./minishell"))
			signal_shell_level(data);
		signal(SIGQUIT, SIG_DFL);
		close(pipe[0]);
		dup2(pipe[1], 1);
		close(pipe[1]);
		if (cmd->input != -8 || cmd->output != -8)
			_redirect(cmd);
		if (check_builtins(cmd->command))
		{
			run_builtins(cmd->command, data);
			exit(0);
		}
		_exec(cmd, data);
	}
	close(pipe[1]);
}

void	middle_cmd(t_command *cmd, t_data *data, int *old_pipe, int *new_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec_midle_cmd(cmd, data, new_pipe, old_pipe);
	close(old_pipe[0]);
	close(new_pipe[1]);
}

void	last_cmd(t_command *cmd, t_data *data, int *pipe)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid != 0)
		update_exit_status(pid);
	if (pid == 0)
	{
		if (_strcmp(cmd->command[0], "./minishell"))
			signal_shell_level(data);
		signal(SIGQUIT, SIG_DFL);
		close(pipe[1]);
		dup2(pipe[0], 0);
		close(pipe[0]);
		if (cmd->input != -8 || cmd->output != -8)
			_redirect(cmd);
		if (check_builtins(cmd->command))
		{
			run_builtins(cmd->command, data);
			exit(0);
		}
		_exec(cmd, data);
	}
	close(pipe[0]);
}

void	_exec(t_command *cmd, t_data *data)
{
	char	*path;

	path = check_cmd(cmd->command[0], data->ev);
	if (!path)
		set_error(path, cmd);
	if (execve(path, cmd->command, _env(data->ev)) == -1)
	{
		if (access(cmd->command[0], F_OK))
		{
			_putstr_fd("minishell$: No such file or directory\n", 2);
			exit(127);
		}
		if (access(cmd->command[0], X_OK))
		{
			_putstr_fd("minishell$: Permission denied\n", 2);
			exit(126);
		}
	}
}
