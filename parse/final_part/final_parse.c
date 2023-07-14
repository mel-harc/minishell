/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:00:48 by houadou           #+#    #+#             */
/*   Updated: 2023/06/19 11:34:13 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**cmd_creation(char **cmd)
{
	char	**new;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		exit(1);
	i = -1;
	while (cmd[++i])
		new[i] = ft_strdup(cmd[i]);
	new[i] = NULL;
	return (new);
}

static int	is_valid(int type, int flag)
{
	if (flag == 0)
		return (type == DB_QUOTE_STRING || type == SG_QUOTE_STRING);
	else if (flag == 1)
		return ((type != WHITE_SPACE && type != PIPE && type != HEAD) && \
		type != DOLLAR);
	else if (flag == 2)
		return ((type != HEREDOC && type != APPEND && type != WHITE_SPACE \
				&& type != PIPE && type != INPUT_RED && type != OUTPUT_RED));
	return (0);
}

void	after_before_quotes(t_token **temp, int flag)
{
	if (flag == 0)
	{
		(*temp)->content = join_strings((*temp)->prev->content, \
										(*temp)->content, 2);
		(*temp) = current_node_erase((*temp)->prev);
	}
	else if (flag == 1)
	{
		(*temp)->content = join_strings((*temp)->content, \
										(*temp)->next->content, 1);
		(*temp) = next_node_erase((*temp)->next);
	}
}

void	merge_quoted_string(t_token **tokens)
{
	t_token	*temp;

	temp = (*tokens)->next;
	while (temp)
	{
		if (temp->content && is_valid(temp->type, 0))
		{
			if (temp->prev->type == DOLLAR)
				temp = current_node_erase(temp->prev);
			if (temp->prev && is_valid(temp->prev->type, 1))
				after_before_quotes(&temp, 0);
			while (temp->next && is_valid(temp->next->type, 2))
				after_before_quotes(&temp, 1);
			if (!temp->next)
				break ;
		}
		temp = temp->next;
	}
}
