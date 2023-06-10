/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:41:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/10 22:45:13 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eexit(char **cmd)
{
	size_t	i;
	int		nbr;

	i = 0;
	if (cmd[1])
	{
		if (ft_strnstr(cmd[1], "-", 1) || ft_strnstr(cmd[1], "+", 1))
			i++;
		while (cmd[1][i])
		{
			if (!ft_strchr("0123456789", cmd[1][i]))
				put_error(1, cmd[1], 255);
			i++;
		}
		nbr = ft_atoi(cmd[1]);
		if (cmd[2])
			put_error(0, cmd[1], 1);
		else
			put_error(2, cmd[1], nbr);
	}
	put_error(3, cmd[1], 0);
}

void	put_error(int flag, char *arg, int nbr)
{
	printf("exit\n");
	if (flag == 0)
		printf("minishell: exit: too many arguments\n");
	if (flag == 1)
		printf("minishell: exit: %s: numeric argument required\n", arg);
	exit(nbr);
}