/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:14:31 by houadou           #+#    #+#             */
/*   Updated: 2023/06/15 15:07:17 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*create_new_command(int output, int input)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		exit(1);
	new->next = NULL;
	new->output = output;
	new->input = input;
	new->command = NULL;
	new->prev = NULL;
	return (new);
}

void	create_addback_cmd(t_command **head, int output, int input, char **cmd)
{
	t_command	*new;
	t_command	*temp;

	new = malloc(sizeof(t_command));
	if (!new)
		exit(1);
	new->next = NULL;
	new->output = output;
	new->input = input;
	new->command = cmd_creation(cmd);
	new->prev = NULL;
	if ((*head)->command == NULL)
	{
		temp = (*head);
		(*head) = new;
		free(temp);
		return ;
	}
	temp = (*head);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}
