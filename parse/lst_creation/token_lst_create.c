/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:47:37 by houadou           #+#    #+#             */
/*   Updated: 2023/06/13 12:37:01 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_new_tok_node(char *content, int token_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(1);
	new->next = NULL;
	new->content = ft_strdup(content);
	new->type = token_type;
	new->prev = NULL;
	return (new);
}

void	create_addback_tok_node(t_token **head, char *content, int token_type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(1);
	new->next = NULL;
	new->content = ft_strdup(content);
	new->type = token_type;
	new->prev = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}
