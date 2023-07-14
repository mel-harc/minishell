/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:46:35 by houadou           #+#    #+#             */
/*   Updated: 2023/07/08 17:11:14 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_word_manage(char *line, t_token **tokens, int *index)
{
	char	*join;
	char	*str_char;

	join = NULL;
	str_char = NULL;
	while (line[*index] && !ft_strchr(NOT_VALID_WORD, line[*index]))
	{
		str_char = manage_string(2, NULL, NULL, line[*index]);
		join = manage_string(1, join, str_char, 0);
		(*index)++;
	}
	(*index)--;
	if (join)
	{
		create_addback_tok_node(tokens, join, VALID_WORD);
		free(join);
	}
	else
		free(join);
}

void	token_variable_manage(char *line, t_token **tokens, int *index)
{
	char	*join;
	char	*str_char;

	join = NULL;
	str_char = NULL;
	create_addback_tok_node(tokens, "$", DOLLAR);
	while (check_conditions(line, *index))
	{
		(*index)++;
		str_char = manage_string(2, NULL, NULL, line[*index]);
		join = manage_string(1, join, str_char, 0);
	}
	if (join)
	{
		create_addback_tok_node(tokens, join, VARIABLE);
		free(join);
	}
	else
		free(join);
}

static int	token_list_size(t_token *tokens)
{
	int		i;
	t_token	*temp_tok;

	i = 0;
	temp_tok = tokens->next;
	while (temp_tok)
	{
		i++;
		temp_tok = temp_tok->next;
	}
	return (i);
}

void	start_token(char *line, t_data *data)
{
	int			i;
	t_token		*tokens;

	if (!check_quotes(line, data))
	{
		g_exit_status = 258;
		return ;
	}
	i = -1;
	tokens = create_new_tok_node("HEAD", HEAD);
	while (line[++i])
		tokens_manage(line, &i, &tokens);
	if (!check_tokens(&tokens))
	{
		g_exit_status = 258;
		return (free_tokens(&tokens));
	}
	start_expand(&tokens, data);
	merge_quoted_string(&tokens);
	data->size_of_list = token_list_size(tokens);
	if (!start_final_parse(&tokens, data))
		return (free_tokens(&tokens));
}
