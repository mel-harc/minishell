/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:24 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/04 22:20:22 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execmds(t_data *data, char **envp)
{
	t_list_cmds	*tmp_cmds;

	tmp_cmds = NULL;
	tmp_cmds = data->head_cmds;
	if (!tmp_cmds->previous && !tmp_cmds->next && tmp_cmds)
		one_cmd(data, envp);
	else
		mlt_cmds(tmp_cmds, data, envp);
	return ;
}

void	mlt_cmds(t_list_cmds *tmp_cmds, t_data *data, char **envp)
{
	int			i;
	int			**pipefd;

	i = 0;
	pipefd = alloc_fds(data->head_cmds);
	pipe(pipefd[i]);
	if (tmp_cmds && tmp_cmds->next && !tmp_cmds->previous)
	{
		first_cmd(data, pipefd[i], envp);
		tmp_cmds = tmp_cmds->next;
	}
	while (tmp_cmds && tmp_cmds->previous && tmp_cmds->next)
	{
		close(pipefd[i][1]);
		pipe(pipefd[++i]);
		middle_cmd(tmp_cmds, data, pipefd[i - 1], pipefd[i], envp);
		tmp_cmds = tmp_cmds->next;
	}
	if (tmp_cmds && tmp_cmds->previous && !tmp_cmds->next)
		last_cmd(tmp_cmds, data, pipefd[i], envp);
	close(pipefd[i][0]);
	close(pipefd[i][1]);
	while (wait(NULL) != -1)
		;
	return ;
}
