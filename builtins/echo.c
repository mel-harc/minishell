/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:37:34 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/11 19:57:39 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **cmd)
{
	int		i;

	if (ft_strnstr(cmd[1], "-", 1) && !search_chr(cmd[1], 'n'))
	{
		i = 2;
		while (ft_strnstr(cmd[i], "-", 1) && !search_chr(cmd[i], 'n'))
			i++;
		if (cmd[i])
			printf("%s", cmd[i]);
		while (cmd[++i])
			printf(" %s", cmd[i]);
	}
	else
	{
		i = 1;
		if (cmd[i])
			printf("%s", cmd[i]);
		while (cmd[++i])
			printf(" %s", cmd[i]);
		printf("\n");
	}
	exit_status = 0;
	exit (0);
}

char	*search_chr(const char *s, int c)
{
	s++;
	while (*s == (char)c || *s == '\0')
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}
