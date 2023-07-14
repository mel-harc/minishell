/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:06:50 by houadou           #+#    #+#             */
/*   Updated: 2023/07/11 10:44:03 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*next_node_erase(t_token *tok)
{
	t_token	*temp;

	if (!tok->prev)
	{
		temp = tok->next;
		tok->next->prev = NULL;
		free(tok->content);
		free(tok);
		return (temp);
	}
	temp = tok->prev;
	if (!tok->next)
	{
		tok->prev->next = NULL;
		free(tok->content);
		free(tok);
	}
	else
	{
		tok->prev->next = tok->next;
		tok->next->prev = tok->prev;
		free(tok->content);
		free(tok);
	}
	return (temp);
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	while (*tokens)
	{
		temp = *tokens;
		*tokens = (*tokens)->next;
		free(temp->content);
		free(temp);
	}
	*tokens = NULL;
}

t_token	*current_node_erase(t_token *tok)
{
	t_token	*temp;
	t_token	*return_temp;

	if (!tok->next)
	{
		temp = tok;
		if (tok->prev)
			tok->prev->next = NULL;
		tok = tok->prev;
		return (free(temp->content), free(temp), tok);
	}
	temp = tok;
	return_temp = (tok)->next;
	if ((tok)->prev)
	{
		(tok)->prev->next = (tok)->next;
		if ((tok)->next)
			(tok)->next->prev = (tok)->prev;
	}
	else
	{
		(tok)->next->prev = NULL;
		tok = (tok)->next;
	}
	return (free(temp->content), free(temp), return_temp);
}
