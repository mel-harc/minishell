/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:16:40 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/11 18:22:33 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(char **cmd)
{
	if (ft_strnstr(cmd[0], "echo", 4))
		return (1);
	else if (ft_strnstr(cmd[0], "cd", 2))
		return (1);
	else if (ft_strnstr(cmd[0], "pwd", 3))
		return (1);
	else if (ft_strnstr(cmd[0], "export", 6))
		return (1);
	else if (ft_strnstr(cmd[0], "unset", 5))
		return (1);
	else if (ft_strnstr(cmd[0], "env", 3))
		return (1);
	else if (ft_strnstr(cmd[0], "exit", 4))
		return (1);
	else
		return (0);
}

int	built_main(char **cmd)
{
	if (ft_strnstr(cmd[0], "cd", 2))
		return (1);
	if (ft_strnstr(cmd[0], "exit", 4))
		return (1);
	return (0);
}

void	run_builtins(char **cmd)
{
	if (ft_strnstr(cmd[0], "echo", 4))
		echo(cmd);
	if (ft_strnstr(cmd[0], "cd", 2))
		cd(cmd);
	if (ft_strnstr(cmd[0], "exit", 4))
		eexit(cmd);
}
