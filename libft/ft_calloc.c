/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:53:44 by houadou           #+#    #+#             */
/*   Updated: 2023/06/11 17:39:51 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	l;		

	if (n >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	l = size * n;
	ptr = (void *)malloc(l);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, l);
	return (ptr);
}
