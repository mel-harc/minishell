/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:59:28 by houadou           #+#    #+#             */
/*   Updated: 2023/06/13 10:57:11 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(str) + 1;
	dup = (char *)malloc(size);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, size);
	return (dup);
}
