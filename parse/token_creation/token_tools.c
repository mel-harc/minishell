/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:26:09 by houadou           #+#    #+#             */
/*   Updated: 2023/06/14 15:28:28 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	next_quote_index(char *str, int *index, char quote)
{
	while (str[++(*index)] && str[*index] != quote)
		;
	return (*index);
}

static void	token_quotes_manage(char *line, int flag, t_token **tokens, int *i)
{
	char	quote;
	int		start;
	int		len;
	char	*str;

	if (!flag)
		quote = '"';
	else
		quote = '\'';
	start = *i;
	len = next_quote_index(line, i, quote) - start;
	if (flag == 0)
		flag = DB_QUOTE_STRING;
	else
		flag = SG_QUOTE_STRING;
	str = ft_substr(line, start + 1, len - 1);
	if (!str)
		return ;
	create_addback_tok_node(tokens, str, flag);
	free(str);
}

static void	token_manage_2(char *line, int *index, t_token **tokens)
{
	if (line[*index] == '"')
		token_quotes_manage(line, 0, tokens, index);
	else if (line[*index] == '\'')
		token_quotes_manage(line, 1, tokens, index);
	else if (line[*index] == '>' && line[*index + 1] == '>')
	{
		create_addback_tok_node(tokens, ">>", APPEND);
		(*index) += 1;
	}
	else if (line[*index] == '<' && line[*index + 1] == '<')
	{
		create_addback_tok_node(tokens, "<<", HEREDOC);
		(*index) += 1;
	}
	else
		token_word_manage(line, tokens, index);
}

void	tokens_manage(char *line, int *index, t_token **tokens)
{
	if (line[*index] == '|')
		create_addback_tok_node(tokens, "|", PIPE);
	else if (line[*index] == '<' && line[*index + 1] != '<')
		create_addback_tok_node(tokens, "<", INPUT_RED);
	else if (line[*index] == '>' && line[*index + 1] != '>')
		create_addback_tok_node(tokens, ">", OUTPUT_RED);
	else if (ft_strchr(WHITE_SPACES, line[*index]))
		create_addback_tok_node(tokens, " ", WHITE_SPACE);
	else if (line[*index] == '$')
		token_variable_manage(line, tokens, index);
	else
		token_manage_2(line, index, tokens);
}
