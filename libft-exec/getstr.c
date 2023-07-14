/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:27:52 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/09 14:58:56 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getstr(char *src)
{
	char	*dst;
	int		i;

	dst = (char *)malloc((_strlen(src) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

int	_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
		return (0);
	else
		return (1);
}

int	_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*find_variable(char *str, int i)
{
	char	*s;
	int		j;

	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		exit(1);
	j = -1;
	while (++j < i)
		s[j] = str[j];
	s[j] = '\0';
	return (s);
}

int	parse_export(char *str)
{
	int	i;

	i = -1;
	if (_isalpha(str[0]))
	{
		g_exit_status = 1;
		_putstr_fd("minishell$: not a valid identifier\n", 2);
		return (1);
	}
	while (str[++i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			break ;
		else if (_strchr("!#$%&'/-+()*,.?@[]\{^|}~", str[i]))
		{
			g_exit_status = 1;
			_putstr_fd("minishell$: not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}
