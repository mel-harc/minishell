/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:06:55 by houadou           #+#    #+#             */
/*   Updated: 2023/06/16 16:13:58 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

int	ft_new_line(const char *str)
{
	while (str && *str && str++)
		if (*str == '\n')
			return (0);
	return (1);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		l;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		*s1 = 0;
	}
	l = gnl_strlen(s1) + gnl_strlen(s2);
	str = (char *)malloc(l + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[l] = 0;
	return (free(s1), str);
}
