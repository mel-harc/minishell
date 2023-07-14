/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:57:07 by houadou           #+#    #+#             */
/*   Updated: 2022/10/07 11:02:52 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	l;

	l = 0;
	if (size)
	{
		while (src[l] && l < size - 1)
		{
			dst[l] = src[l];
			l++;
		}
		dst[l] = 0;
	}
	return (ft_strlen(src));
}
