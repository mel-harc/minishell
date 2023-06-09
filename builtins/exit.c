/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:41:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/09 23:03:03 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eexit(char **cmd)
{
	size_t	i;

	i = 0;
	if (cmd[1])
	{
		ft_atoi(cmd[1]);
		if (ft_strnstr(cmd[1], "-", 1) || ft_strnstr(cmd[1], "+", 1))
			i++;
		while (cmd[1][i])
		{
			if (!ft_strchr("0123456789", cmd[1][i]))
				put_error(1, cmd[1]);		
			i++;
		}
		if (cmd[2])
			put_error(0, cmd[1]);
			
	}
}

void	put_error(int i, char *arg)
{
	if (i == 0)
	{
		printf("exit: too many arguments\n");
		exit(-1);
	}
	if (i == 1)
	{
		printf("exit: %s: numeric argument required\n", arg);
		exit(-1);
	}
}