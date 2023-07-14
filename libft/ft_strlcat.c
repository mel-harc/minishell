/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:06:23 by houadou           #+#    #+#             */
/*   Updated: 2022/10/14 08:53:01 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (dstsize == 0 && !dst)
		return (ft_strlen(src));
	j = 0;
	i = ft_strlen(dst);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	if (dstsize > (dst_len + src_len))
		dstsize = dst_len + src_len + 1;
	if (dstsize > dst_len + 1)
		while (i < dstsize - 1)
			dst[i++] = src[j++];
	dst[i] = 0;
	return (dst_len + src_len);
}
