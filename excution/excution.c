/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:24 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/31 16:16:04 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execmds(t_data *data, char **envp)
{
	t_list_cmds	*tmp_cmds;
	int			pipefd[2];

	tmp_cmds = NULL;
	tmp_cmds = data->head_cmds;
	if (!tmp_cmds->previous && !tmp_cmds->next && tmp_cmds)
		one_cmd(data, envp);
	else
	{
		pipe(pipefd);
		if (tmp_cmds && tmp_cmds->next && !tmp_cmds->previous)
		{
			first_cmd(data, pipefd, envp);
			tmp_cmds = tmp_cmds->next;
		}
		while (tmp_cmds && tmp_cmds->previous && tmp_cmds->next)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			pipe(pipefd);
			middle_cmd(tmp_cmds, data, pipefd, envp);
			tmp_cmds = tmp_cmds->next;
		}
		if (tmp_cmds && tmp_cmds->previous && !tmp_cmds->next)
			last_cmd(tmp_cmds, data, pipefd, envp);
		close(pipefd[0]);
		close(pipefd[1]);
		while (wait(NULL) != -1)
			;
	}
	return ;
}

void	last_cmd(t_list_cmds *cmd, t_data *data, int *pipe, char **envp)
{
	int	pid;
	char	**arg;

	pid = fork();
	if (pid == 0)
	{
		close(pipe[1]);
		dup2(pipe[0], 0);
		close(pipe[0]);
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = cmd->cmd;
		arg[1] = NULL;
		execve(check_cmd(cmd->cmd, data->paths), arg, envp);
		return ;
	}
}

char *check_cmd(char *cmd, char **paths)
{
	int		i;
	char	*str;
	char	*ncmd;

	i = 0;
	ncmd = ft_strjoin("/", cmd);
	if (!ncmd)
		return (NULL);
	while (paths[++i])
	{
		str = ft_strjoin(paths[i], ncmd);
		if (!str)
			return (NULL);
		if (!access(str, F_OK | X_OK))
			return (str);
		free(str);
	}
	free(ncmd);
	return (NULL);
}

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
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = head_cmds->cmd;
		arg[1] = NULL;
		execve(check_cmd(head_cmds->cmd, data->paths), arg, envp);
		free(arg);
		return;
	}
	return ;
}

void	first_cmd(t_data *data, int *pipe, char **envp)
{
	int	pid;
	char	**arg;
	t_list_cmds	*head_cmds;

	pid = fork();
	head_cmds = NULL;
	head_cmds = data->head_cmds;
	if (pid == 0)
	{
		close(pipe[0]);
		dup2(pipe[1], 1);
		close(pipe[1]);
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = head_cmds->cmd;
		arg[1] = NULL;
		execve(check_cmd(head_cmds->cmd, data->paths), arg, envp);
		free(arg);
		return ;
	}
}

void	middle_cmd(t_list_cmds *cmd, t_data *data, int *pipefd, char **envp)
{
	char **arg;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], 0);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = cmd->cmd;
		arg[1] = NULL;
		execve(check_cmd(cmd->cmd, data->paths), arg, envp);
		return ;
	}
}