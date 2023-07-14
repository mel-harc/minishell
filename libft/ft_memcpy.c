/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:41:08 by houadou           #+#    #+#             */
/*   Updated: 2022/10/11 14:49:07 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	int	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	while (++i < (int)size)
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
	return (dst);
}
