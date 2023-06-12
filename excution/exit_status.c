/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:21:03 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/12 21:16:27 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	status_of_exit(int status)
{
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		exit_status = WSTOPSIG(status) + 128;
	if (WIFSIGNALED(status))
	{
		if (128 + WTERMSIG(status) == 130)
			_putstr_fd("\n", 2);
		if (128 + WTERMSIG(status) == 131)
			_putstr_fd("Quit: 3\n", 2);
		exit_status = WTERMSIG(status) + 128;
	}
	exit_status = 1;
}

void	set_error(void)
{
	if (errno == EACCES)
	{
		_putstr_fd("minishell: Permission denied\n", 2);
		exit_status = 126;
	}
	if (errno == ENOENT)
	{
		_putstr_fd("minishell: No such file or directory\n", 1);
		exit_status = 1;
	}
}