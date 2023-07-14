/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expande2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:08:14 by houadou           #+#    #+#             */
/*   Updated: 2023/06/15 18:19:36 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_env(char *str, t_data *data)
{
	t_env	*env;
	char	*tmp;

	if (str[0] == '?' && str[1] == '\0')
		return (ft_itoa(g_exit_status));
	if (str[0] == '?' && str[1] != '\0' && str[2] != '$')
	{
		tmp = join_strings(ft_itoa(g_exit_status), str + 1, 1);
		free(str);
		return (tmp);
	}
	env = data->ev;
	while (env)
	{
		if (ft_strcmp(env->variable, str) == 0)
		{
			free(str);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free(str);
	return (NULL);
}

static char	*is_valid_env(char *str, int *i)
{
	char	*tmp;
	int		j;
	int		after_dollar;

	j = 0;
	after_dollar = *i + 1;
	while (str[++(*i)])
	{
		if (str[*i] == '$' || str[*i] == '\"' || str[*i] == '\'' || \
		ft_strchr(WHITE_SPACES, str[*i]) || ft_strchr(SPECIAL_CHAR, str[*i]))
			break ;
		j++;
	}
	if (j == 0)
		return (NULL);
	tmp = ft_substr(str, after_dollar, j);
	return (tmp);
}

static void	expand_free_all(char *tmp, char *tmp2, char *str)
{
	free(tmp);
	free(tmp2);
	free(str);
}

static void	quoted_expand_merge(t_token **temp, char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	if ((*temp)->content[i] != '\0')
		tmp = ft_substr((*temp)->content, i, ft_strlen((*temp)->content));
	free((*temp)->content);
	(*temp)->content = join_strings(str, tmp, 0);
}

void	quoted_expand(t_token **temp, t_data *data)
{
	char	*str;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while ((*temp)->content[i])
	{
		if ((*temp)->content[i] == '$')
		{
			str = ft_strdup((*temp)->content);
			tmp = ft_substr(str, 0, i);
			tmp2 = is_valid_env(str, &i);
			if (tmp2 == NULL)
			{
				expand_free_all(tmp, tmp2, str);
				return ;
			}
			free(str);
			str = join_strings(tmp, get_env(tmp2, data), 0);
			quoted_expand_merge(temp, str, i);
			i = 0;
		}
		i++;
	}
}
