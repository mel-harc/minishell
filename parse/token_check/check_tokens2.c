/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:29:54 by houadou           #+#    #+#             */
/*   Updated: 2023/06/21 15:34:27 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid(int type, int flag)
{
	if (flag)
		return (type != PIPE && type != WHITE_SPACE);
	else
		return (type == DB_QUOTE_STRING || type == SG_QUOTE_STRING);
}

static void	type_of_delimiter(t_token **tok, int here_flag, int quotes_flag)
{
	if (here_flag == 1 && quotes_flag == 1)
		(*tok)->type = QUOTED_DELIM;
	else
		(*tok)->type = SIMPLE_DELIM;
}

static void	join_quoted_delimiter(t_token **temp_tok)
{
	while ((*temp_tok)->next && is_valid((*temp_tok)->next->type, 1))
	{
		(*temp_tok)->content = join_strings((*temp_tok)->content, \
		(*temp_tok)->next->content, 1);
		*temp_tok = next_node_erase((*temp_tok)->next);
	}
	(*temp_tok)->type = QUOTED_DELIM;
}

static void	check_heredoc_delimiter(t_token **temp_tok, int here_flag)
{
	int		quotes_flag;

	quotes_flag = 0;
	if (here_flag == 1 && ((*temp_tok)->type == DOLLAR || \
	(*temp_tok)->type == VALID_WORD))
	{
		while ((*temp_tok)->next && is_valid((*temp_tok)->next->type, 1))
		{
			if (is_valid((*temp_tok)->next->type, 0))
				quotes_flag = 1;
			(*temp_tok)->content = join_strings((*temp_tok)->content, \
			(*temp_tok)->next->content, 1);
			(*temp_tok) = next_node_erase((*temp_tok)->next);
		}
	}
	type_of_delimiter(temp_tok, here_flag, quotes_flag);
}

int	check_redirection(t_token **tokens)
{
	t_token	*temp_tok;
	int		here_flag;

	if ((*tokens)->type == HEREDOC)
		here_flag = 1;
	temp_tok = (*tokens)->next;
	while (temp_tok)
	{
		if (is_valid(temp_tok->type, 0))
		{
			if (here_flag == 1)
				join_quoted_delimiter(&temp_tok);
			return (1);
		}
		if (temp_tok->type == DOLLAR || temp_tok->type == VALID_WORD)
			return (check_heredoc_delimiter(&temp_tok, here_flag), 1);
		else if (temp_tok->type == WHITE_SPACE)
			temp_tok = temp_tok->next;
		else
			return (write(2, ERROR_REDIR, ft_strlen(ERROR_REDIR)), 0);
	}
	return (write(2, ERROR_REDIR, ft_strlen(ERROR_REDIR)), 0);
}
