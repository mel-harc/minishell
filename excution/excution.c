/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:24 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/24 22:53:58 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execmds(t_data *data, char **envp)
{
	t_list_cmds	*head_cmds;
	int			pipefd[2];

	head_cmds = NULL;
	head_cmds = data->head_cmds;
	if (!head_cmds->previous && !head_cmds->next && head_cmds)
	{
		one_cmd(data, envp);
		return ;
	}
	if (pipe(pipefd) == -1)
	{
		printf("Error in function pipe\n");
		exit(1);
	}
	if (head_cmds && head_cmds->next && !head_cmds->previous)
		first_cmd(data, pipefd, envp);
	head_cmds = head_cmds->next;
	if (head_cmds && head_cmds->previous && !head_cmds->next)
		last_cmd(head_cmds, data, pipefd, envp);
	
	return ;
}

void	last_cmd(t_list_cmds *cmd, t_data *data, int *pipefd, char **envp)
{
	int	pid;
	char	**arg;
	int		status;

	pid = fork();
	if (pid == -1 || pid != 0)
	{
		waitpid(pid, &status, 0);
		return ;
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 0);
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = cmd->cmd;
		arg[1] = NULL;
		execve(check_cmd(cmd->cmd, data->paths), arg, envp);
		close(pipefd[1]);
		free(arg);
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
	int			pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
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

void	first_cmd(t_data *data, int *pipefd, char **envp)
{
	int	pid;
	int	status;
	char	**arg;
	t_list_cmds	*head_cmds;

	pid = fork();
	head_cmds = NULL;
	head_cmds = data->head_cmds;
	if (pid == -1 || pid != 0)
	{
		waitpid(pid, &status, 0);
		return ;
	}
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 1);
		arg = (char **)malloc(sizeof(char *) * 2);
		if (!arg)
			return ;
		arg[0] = head_cmds->cmd;
		arg[1] = NULL;
		execve(check_cmd(head_cmds->cmd, data->paths), arg, envp);
		free(arg);
		close(pipefd[0]);
		return ;
	}
}