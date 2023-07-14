/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:16:04 by houadou           #+#    #+#             */
/*   Updated: 2023/06/13 12:47:22 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	valid_token_type(int type, int flag)
{
	if (flag)
		return (type == VALID_WORD || type == DOLLAR || \
				type == DB_QUOTE_STRING || type == SG_QUOTE_STRING || \
				type == INPUT_RED || type == OUTPUT_RED || \
				type == HEREDOC || type == APPEND);
	else
		return (type == VALID_WORD || type == DOLLAR || \
				type == DB_QUOTE_STRING || type == SG_QUOTE_STRING || \
				type == VARIABLE || type == SIMPLE_DELIM || \
				type == QUOTED_DELIM);
}

static int	check_after_before_pipes(t_token *tokens)
{
	t_token	*temp_tok;

	temp_tok = tokens->next;
	if (!temp_tok)
		return (0);
	while (temp_tok)
	{
		if (valid_token_type(temp_tok->type, 1))
			return (1);
		else if (temp_tok->type == WHITE_SPACE)
			temp_tok = temp_tok->next;
		else
			return (0);
	}
	temp_tok = tokens->prev;
	while (temp_tok)
	{
		if (valid_token_type(temp_tok->type, 0))
			return (1);
		else if (temp_tok->type == WHITE_SPACE)
			temp_tok = temp_tok->prev;
		else
			return (0);
	}
	return (0);
}

static int	check_pipes(t_token *tok)
{
	if (!check_after_before_pipes(tok))
		return (write(2, ERROR_PIPES, ft_strlen(ERROR_PIPES)), 0);
	return (1);
}

int	check_tokens(t_token **tokens)
{
	t_token	*tok;

	tok = *tokens;
	if (tok->type == PIPE)
		return (write(2, ERROR_PIPES, ft_strlen(ERROR_PIPES)), 0);
	while (tok)
	{
		if (tok->type == INPUT_RED || tok->type == OUTPUT_RED || \
		tok->type == HEREDOC || tok->type == APPEND)
			if (!check_redirection(&tok))
				return (0);
		if (tok->type == PIPE)
			if (!check_pipes(tok))
				return (0);
		tok = tok->next;
	}
	return (1);
}
