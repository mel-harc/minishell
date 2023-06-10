/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:22 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/10 23:01:29 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	int				sign;
	size_t			rest;

	i = 0;
	sign = 1;
	rest = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		rest = rest * 10 + str[i] - 48;
		if (rest - 1 > 9223372036854775807 && sign == -1)
			put_error(1, (char *)str, rest);
		else if (rest > 9223372036854775807 && sign == 1)
			put_error(1, (char *)str, rest);
		i++;
	}
	return (rest * sign);
}