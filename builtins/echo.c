/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:37:34 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/07 16:05:23 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **cmd)
{
	int		i;
	
	if (ft_strnstr(cmd[1], "-n", 2))
	{
		i = 2;
		printf("%s", ft_strtrim(cmd[i], "\"\""));
		while (cmd[++i])
			printf(" %s", ft_strtrim(cmd[i], "\"\""));
	}
	else
	{
		i = 1;
		printf("%s", ft_strtrim(cmd[i], "\"\""));
		while (cmd[++i])
			printf(" %s", ft_strtrim(cmd[i], "\"\""));
		printf("\n");
	}
	exit (0);
}