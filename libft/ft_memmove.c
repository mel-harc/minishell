/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:01:19 by houadou           #+#    #+#             */
/*   Updated: 2022/10/07 12:41:56 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	if (dst > src)
	{
		while (size--)
			*((unsigned char *)dst + size) = *((unsigned char *)src + size);
	}
	else
		ft_memcpy(dst, src, size);
	return (dst);
}
