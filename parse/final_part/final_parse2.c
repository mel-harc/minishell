/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:19 by houadou           #+#    #+#             */
/*   Updated: 2023/07/10 21:09:56 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	finally_is_valid(int type, int flag)
{
	if (flag == 0)
		return ((type != WHITE_SPACE && type != PIPE));
	else if (flag == 1)
		return ((type == HEREDOC || type == APPEND || \
				type == INPUT_RED || type == OUTPUT_RED));
	else if (flag == 2)
		return (type == OUTPUT_RED);
	else if (flag == 3)
		return (type == APPEND);
	else if (flag == 4)
		return (type == INPUT_RED);
	else if (flag == 5)
		return (type == HEREDOC);
	else if (flag == 6)
		return (type == PIPE);
	else if (flag == 7)
		return (type != DB_QUOTE_STRING && type != SG_QUOTE_STRING \
				&& type != QUOTED_DELIM);
	return (0);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

static int	create_command(char ***str, t_command **cmd, t_token *temp, \
t_data *data)
{
	create_addback_cmd(cmd, data->output, data->input, *str);
	if (temp->next)
	{
		ft_free(*str);
		*str = malloc(sizeof(char *) * (data->size_of_list));
		if (!*str)
			return (0);
	}
	else
	{
		ft_free(*str);
		*str = NULL;
	}
	data->input = -8;
	data->output = -8;
	return (1);
}

static int	start_checking(t_token *temp, t_data *data, t_command **cmd, \
char **str)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (finally_is_valid(temp->type, 1))
			redirection_manage(data, &temp);
		else if (finally_is_valid(temp->type, 0))
			str[i++] = ft_strdup(temp->content);
		if (!temp->next || finally_is_valid(temp->type, 6))
		{
			str[i] = NULL;
			i = 0;
			if (!create_command(&str, cmd, temp, data))
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	start_final_parse(t_token **tokens, t_data *data)
{
	t_token		*temp;
	t_command	*cmd;
	char		**str;

	str = malloc(sizeof(char *) * (data->size_of_list));
	if (!str)
		return (0);
	cmd = create_new_command(-8, -8);
	temp = (*tokens)->next;
	if (!temp)
		return (0);
	data->input = -8;
	data->output = -8;
	if (!start_checking(temp, data, &cmd, str))
		return (0);
	free_tokens(tokens);
	execmds(&cmd, data);
	free_commands(&cmd);
	return (1);
}
