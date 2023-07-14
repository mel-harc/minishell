/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:48:05 by houadou           #+#    #+#             */
/*   Updated: 2022/10/18 10:26:23 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	l;

	l = ft_strlen(str);
	while (l >= 0)
	{
		if (str[l] == (char) c)
			return ((char *)str + l);
		l--;
	}
	return (NULL);
}
