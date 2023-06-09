/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:44:16 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/09 18:13:25 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **cmd)
{
	if (chdir(cmd[1]) == 0)
		return ;
	else
	{
		printf("cd: %s: No such file or directory\n", cmd[1]);
		return ;
	}
}
