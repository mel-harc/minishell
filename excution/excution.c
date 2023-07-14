/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:24 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/08 17:30:56 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execmds(t_command **cmd, t_data *data)
{
	data->std_int = dup(0);
	data->std_out = dup(1);
	if (!(*cmd)->command[0] && !(*cmd)->next)
		return ;
	if (*cmd && !(*cmd)->prev && !(*cmd)->next)
		one_cmd(cmd, data);
	else
		mlt_cmds(cmd, data);
	close(data->std_int);
	close(data->std_out);
	dup2(data->std_int, 0);
	dup2(data->std_out, 1);
	return ;
}

void	mlt_cmds(t_command **cmds, t_data *data)
{
	int			**pipefd;
	int			status;
	t_command	*tmp_cmd;

	status = 0;
	tmp_cmd = (*cmds);
	pipefd = alloc_fds(tmp_cmd);
	loop_cmds(tmp_cmd, pipefd, data);
	while (wait(0) != -1)
		;
	free_fd(pipefd);
}

void	loop_cmds(t_command *tmp_cmd, int **pipefd, t_data *data)
{
	int	i;

	i = 0;
	pipe(pipefd[i]);
	while (tmp_cmd)
	{
		if (tmp_cmd && tmp_cmd->next && !tmp_cmd->prev)
			first_cmd(tmp_cmd, pipefd[i], data);
		else if (tmp_cmd && tmp_cmd->prev && tmp_cmd->next)
		{
			pipe(pipefd[++i]);
			middle_cmd(tmp_cmd, data, pipefd[i - 1], pipefd[i]);
		}
		else if (tmp_cmd && tmp_cmd->prev && !tmp_cmd->next)
			last_cmd(tmp_cmd, data, pipefd[i]);
		tmp_cmd = tmp_cmd->next;
	}
}

void	free_fd(int **array_fd)
{
	int	i;

	i = -1;
	while (array_fd[++i])
		free(array_fd[i]);
	free(array_fd);
}

void	update_exit_status(pid_t pid)
{
	int	status;

	g_exit_status = -13;
	waitpid(pid, &status, 0);
	status_of_exit(status);
}
