/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:35:33 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/10 13:19:11 by mel-harc         ###   ########.fr       */
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
		nbr = _atoi(cmd[1]);
		if (cmd[2])
		{
			put_error(0, cmd[1], 257);
			return ;
		}
		else
			put_error(2, cmd[1], nbr);
	}
	put_error(2, cmd[1], 0);
}

void	put_error(int flag, char *arg, int nbr)
{
	(void)arg;
	if (flag == 0)
	{
		_putstr_fd("exit\n", 2);
		g_exit_status = 1;
		_putstr_fd("minishell$: exit: too many arguments\n", 2);
	}	
	else if (flag == 1)
	{
		_putstr_fd("exit\n", 2);
		_putstr_fd("minishell$: exit: numeric argument required\n", 2);
		exit(nbr);
	}
	else if (flag == 2)
	{
		_putstr_fd("exit\n", 1);
		exit(nbr);
	}
}
