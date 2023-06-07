/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:18:16 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/07 16:24:47 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_data *data, char **envp)
{
	int			pid;
	int			status;
	t_list_cmds	*head_cmds;
	char		**arg;

	head_cmds = NULL;
	head_cmds = data->head_cmds;
	pid = fork();
	if (pid == -1 || pid != 0)
	{
		waitpid(pid, &status, 0);
		return ;
	}
	if (pid == 0)
	{
		if (check_builtins(head_cmds->cmd))
			run_builtins(head_cmds->cmd);
		arg = (char **)malloc(sizeof(char *) * 3);
		if (!arg)
			return ;
		arg = head_cmds->cmd;
		execve(check_cmd(head_cmds->cmd[0], data->paths), arg, envp);
	}
	return ;
}

void	first_cmd(t_data *data, int *pipe, char **envp)
{
	pid_t		pid;
	char		**arg;
	t_list_cmds	*head_cmds;

	head_cmds = NULL;
	head_cmds = data->head_cmds;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipe[0]);
		dup2(pipe[1], 1);
		close(pipe[1]);
		if (check_builtins(head_cmds->cmd))
			run_builtins(head_cmds->cmd);
		arg = (char **)malloc(sizeof(char *) * 3);
		if (!arg)
			return ;
		arg = head_cmds->cmd;
		execve(check_cmd(head_cmds->cmd[0], data->paths), arg, envp);
		return ;
	}
}

void	middle_cmd(t_list_cmds *cmd, t_data *data, int *old_pipe, int *new_pipe, char **envp)
{
	char	**arg;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(new_pipe[0]);
		close(old_pipe[1]);
		dup2(old_pipe[0], 0);
		dup2(new_pipe[1], 1);
		close(old_pipe[0]);
		close(new_pipe[1]);
		if (check_builtins(cmd->cmd))
			run_builtins(cmd->cmd);
		arg = (char **)malloc(sizeof(char *) * 3);
		if (!arg)
			return ;
		arg = cmd->cmd;
		execve(check_cmd(cmd->cmd[0], data->paths), arg, envp);
		return ;
	}
}

void	last_cmd(t_list_cmds *cmd, t_data *data, int *pipe, char **envp)
{
	int		pid;
	char	**arg;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipe[1]);
		dup2(pipe[0], 0);
		close(pipe[0]);
		if (check_builtins(cmd->cmd))
			run_builtins(cmd->cmd);
		arg = (char **)malloc(sizeof(char *) * 3);
		if (!arg)
			return ;
		arg = cmd->cmd;
		execve(check_cmd(cmd->cmd[0], data->paths), arg, envp);
		return ;
	}
}
