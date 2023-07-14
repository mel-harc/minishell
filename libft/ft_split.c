/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:32:19 by houadou           #+#    #+#             */
/*   Updated: 2022/12/05 11:55:37 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	total_of_arr(char *s, char c)
{
	int	t;

	t = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			t++;
		}
	}
	return (t);
}

static char	**ft_free(char **s, int index)
{
	while (--index >= 0)
		free(s[index]);
	free(s);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**str;

	str = (char **)malloc(sizeof(char *) * total_of_arr((char *)s, c) + 1);
	if (!str || !s)
		return (NULL);
	i = -1;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j = 0;
			while (*s && *s != c && s++)
				j++;
			str[++i] = (char *)malloc(sizeof(char) * j + 1);
			if (!str[i])
				return (ft_free(str, i));
			ft_strlcpy(str[i], s - j, j + 1);
		}
	}
	str[i + 1] = NULL;
	return (str);
}
