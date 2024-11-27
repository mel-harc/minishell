/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:18:52 by houadou           #+#    #+#             */
/*   Updated: 2023/07/11 10:41:07 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	white_spaces_erase(t_token **temp)
{
	(*temp) = (*temp)->next;
	while ((*temp)->type == WHITE_SPACE)
		(*temp) = current_node_erase(*temp);
}

void	if_not_existed_variable(t_token **temp, int existed_variable)
{
	if (existed_variable == 0)
		(*temp) = current_node_erase((*temp));
	if (temp && (*temp)->prev && (*temp)->prev->content[0] != '>' && \
		(*temp)->prev->content[0] != '<')
		(*temp)->type = DB_QUOTE_STRING;
}

static void	variable_expand(t_token **temp, t_data *data)
{
	t_env	*env;
	char	*value;
	char	*key;
	int		existed_variable;

	env = data->ev;
	existed_variable = 0;
	key = ft_substr((*temp)->content, 0, ft_strlen((*temp)->content));
	while (env)
	{
		if (ft_strcmp(env->variable, key) == 0)
		{
			value = ft_strdup(env->value);
			free((*temp)->content);
			(*temp)->content = ft_strdup(value);
			existed_variable = 1;
			free(value);
			break ;
		}
		env = env->next;
	}
	(*temp) = current_node_erase((*temp)->prev);
	if_not_existed_variable(temp, existed_variable);
	free(key);
}

static void	question_mark(t_token **temp, int flag)
{
	char	*str;

	if (!flag)
	{
		free((*temp)->content);
		(*temp)->content = ft_itoa(g_exit_status);
		(*temp) = current_node_erase(((*temp)->prev));
		(*temp)->type = DB_QUOTE_STRING;
	}
	else if (flag)
	{
		str = ft_strdup((*temp)->content + 1);
		free((*temp)->content);
		(*temp)->content = ft_itoa(g_exit_status);
		(*temp)->content = ft_strjoin((*temp)->content, str);
		(*temp) = current_node_erase(((*temp)->prev));
		free(str);
		(*temp)->type = DB_QUOTE_STRING;
	}
}

void	start_expand(t_token **tokens, t_data *data)
{
	t_token	*temp;

	temp = (*tokens)->next;
	while (temp)
	{
		if (temp->type == WHITE_SPACE)
			white_spaces_erase(&temp);
		if (temp->type == DB_QUOTE_STRING)
			quoted_expand(&temp, data);
		if (temp->type == VARIABLE && temp->content[0] == '?')
		{
			if (temp->content[1] == '\0')
				question_mark(&temp, 0);
			else
				question_mark(&temp, 1);
		}
		else if (temp->type == VARIABLE)
			variable_expand(&temp, data);
		if (!temp)
			break ;
		temp = temp->next;
	}
}
