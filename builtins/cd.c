/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:44:16 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/12 21:17:31 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **cmd)
{
	int	exit;
	
	exit = chdir(cmd[1]);
	if (exit == 0)
		return ;
	else
	{
		exit_status = 1;
		_putstr_fd("cd: No such file or directory\n", 2);
		return ;
	}
}
