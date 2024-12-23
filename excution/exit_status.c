/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:21:03 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/08 18:43:55 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	status_of_exit(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSTOPPED(status))
		g_exit_status = WSTOPSIG(status) + 128;
	else if (WIFSIGNALED(status))
	{
		if (128 + WTERMSIG(status) == 130)
			_putstr_fd("\n", 2);
		if (128 + WTERMSIG(status) == 131)
			_putstr_fd("Quit: 3\n", 2);
		g_exit_status = WTERMSIG(status) + 128;
	}
}
