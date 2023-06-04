/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:28:01 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/04 22:32:27 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getstr(char *src)
{
	char	*dst;
	int		i;

	dst = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
