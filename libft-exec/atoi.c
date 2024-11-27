/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
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

static	size_t	ft_count(int n)
{
	size_t			l;

	l = 0;
	if (n == -2147483648)
		return (11);
	if (n <= 0)
		l++;
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char	*_itoa(int n)
{
	char			*str;
	unsigned int	l;
	long int		nb;

	l = ft_count(n);
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	nb = n;
	str[l] = '\0';
	if (nb == 0)
		str[l - 1] = 48;
	if (n < 0)
	{
		str[0] = 45;
		nb = -nb;
	}
	while (nb)
	{
		str[l - 1] = ((nb % 10) + 48);
		nb /= 10;
		l--;
	}
	return (str);
}
