/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:27:25 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/23 22:07:58 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_atoi(const char *str)
{
	int					sign;
	size_t				i;
	unsigned long long	rest;

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
			put_error(1, (char *)str, 255);
		else if (rest > 9223372036854775807 && sign == 1)
			put_error(1, (char *)str, 255);
		i++;
	}
	return (rest * sign);
}
