/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:16:22 by houadou           #+#    #+#             */
/*   Updated: 2022/10/18 10:47:09 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l_ofs2;

	l_ofs2 = (int)ft_strlen(s2);
	if (*s2 == '\0')
		return ((char *)s1);
	i = 0;
	if (len)
	{
		while (s1[i] && i < len)
		{
			j = 0;
			while (s2[j] && i + j < len && s2[j] == s1[i + j])
				j++;
			if (j == l_ofs2)
				return ((char *)s1 + i);
			i++;
		}
	}
	return (NULL);
}
