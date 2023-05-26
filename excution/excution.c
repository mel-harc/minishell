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
	pid_t		pid;
	t_list_cmds	*head_cmds;
	char		**arg;
	int			pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	head_cmds = NULL;
	head_cmds = data->head_cmds;
	if (!head_cmds->previous && !head_cmds->next)
	{
		pid = fork();
		if (pid == -1 || pid != 0)
		{
			usleep(30000);
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
	while (head_cmds)
	{
		pid = fork();
		if (pid == 1 || pid != 0)
		{
			
		}
		if (pid == 0)
		{
			if (!head_cmds->previous || (!head_cmds->previous && !head_cmds->next))
			{
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
		head_cmds = head_cmds->next;
	}
	return ;
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