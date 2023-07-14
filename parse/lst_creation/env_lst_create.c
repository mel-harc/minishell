/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:33:42 by houadou           #+#    #+#             */
/*   Updated: 2023/07/07 14:19:53 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*create_new_env_node(char *variable, char *value)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		exit(1);
	head->next = NULL;
	head->variable = ft_strdup(variable);
	head->value = ft_strdup(value);
	head->declare = ft_strdup("declare -x");
	head->prev = NULL;
	return (head);
}

void	create_and_addback_env_node(t_env **head, char *variable, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	if (!variable)
		return ;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		exit(1);
	new_node->next = NULL;
	new_node->variable = ft_strdup(variable);
	new_node->value = NULL;
	if (value)
		new_node->value = ft_strdup(value);
	new_node->declare = ft_strdup("declare -x");
	new_node->prev = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}
