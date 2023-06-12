/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:29:51 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/12 20:29:53 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = (char *)haystack;
	if (needle[i] == '\0')
		return (str);
	if (len == 0)
		return (0);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while ((needle[j] == str[i + j] && str[i + j] != '\0') && i + j < len)
			j++;
		if (needle[j] == '\0')
			return (str + i);
		i++;
	}
	return (0);
}