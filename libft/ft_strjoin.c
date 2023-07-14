/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:36:44 by houadou           #+#    #+#             */
/*   Updated: 2022/10/11 09:29:05 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	l1;
	size_t	l2;
	size_t	l;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	l = l1 + l2;
	str = (char *)malloc(sizeof(char) * l + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l + 1);
	return (str);
}
