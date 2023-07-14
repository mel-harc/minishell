/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:06:41 by houadou           #+#    #+#             */
/*   Updated: 2023/06/15 11:44:02 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	l;
	char	*r;

	if (!str)
		return (NULL);
	l = ft_strlen(str);
	if (start >= l)
		return (ft_strdup(""));
	if (start + len > l)
		len = l - start;
	r = (char *)malloc(sizeof(char) * len + 1);
	if (!r)
		return (NULL);
	ft_strlcpy(r, str + start, len + 1);
	return (r);
}
