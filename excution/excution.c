/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:24 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/30 18:36:49 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execmds(t_data *data, char **envp)
{
	t_list_cmds	*head_cmds;
	int			pipe1[2];
	int			pipe2[2];

	head_cmds = NULL;
	head_cmds = data->head_cmds;
	if (!head_cmds->previous && !head_cmds->next && head_cmds)
	{
		one_cmd(data, envp);
		return ;
	}
	if (head_cmds && head_cmds->next && !head_cmds->previous)
	{
		pipe(pipe1);
		first_cmd(data, pipe1, envp);
		head_cmds = head_cmds->next;
	}
	if (head_cmds && head_cmds->previous && head_cmds->next)
	{
		pipe(pipe2);
		middle_cmd(head_cmds, data, pipe1, pipe2, envp);
		head_cmds = head_cmds->next;
	}
	if (head_cmds && head_cmds->previous && !head_cmds->next)
		last_cmd(head_cmds, data, pipe2, envp);
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	while (wait(NULL) != -1)
		;
	
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

void	middle_cmd(t_list_cmds *cmd, t_data *data, int *pipe1, int *pipe2, char **envp)
{
	char **arg;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		close(pipe2[1]);
		close(pipe1[0]);
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = cmd->cmd;
		arg[1] = NULL;
		execve(check_cmd(cmd->cmd, data->paths), arg, envp);
		return ;
	}
}