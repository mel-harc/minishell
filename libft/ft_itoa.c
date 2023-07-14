/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:40:59 by houadou           #+#    #+#             */
/*   Updated: 2022/10/11 11:55:30 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	total_of_char(int n)
{
	int				t;
	unsigned int	num;

	t = 1;
	num = n;
	if (n < 0)
	{
		num = -n;
		t = 2;
	}
	while (num > 9)
	{
		num /= 10;
		t++;
	}
	return (t);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*str;
	int				i;

	if (!n)
		return (ft_strdup("0"));
	i = total_of_char(n);
	num = n;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		num = -n;
		str[0] = '-';
	}
	str[i] = 0;
	while (num > 0)
	{
		str[--i] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
