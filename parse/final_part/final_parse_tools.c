/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:00:14 by houadou           #+#    #+#             */
/*   Updated: 2023/07/10 10:51:27 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	white_spaces_skip(t_token **tokens)
{
	*tokens = (*tokens)->next;
	while ((*tokens)->next && (*tokens)->type == WHITE_SPACE)
		*tokens = (*tokens)->next;
}

static void	output_redirection(t_data *data, t_token **tokens)
{
	int		fd;

	fd = 0;
	if (data->output != -8)
		fd = close(data->output);
	if (fd == -1)
		perror("minishell$>");
	white_spaces_skip(tokens);
	if ((*tokens)->type == WHITE_SPACE)
	{
		perror("minishell$>");
		return ;
	}
	data->output = open((*tokens)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->output == -1)
		perror("minishell$>");
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
}

static void	append(t_data *data, t_token **tokens)
{
	int		fd;

	fd = data->output;
	if (data->output != -8)
		fd = close(data->output);
	if (fd == -1)
		perror("minishell$>");
	white_spaces_skip(tokens);
	if ((*tokens)->type == WHITE_SPACE)
	{
		perror("minishell$>");
		return ;
	}
	data->output = open((*tokens)->content, O_WRONLY | O_CREAT | O_APPEND, \
	0644);
	if (data->output == -1)
		perror("minishell$>");
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
}

static void	input_redirection(t_data *data, t_token **tokens)
{
	if (data->input != -8)
		close(data->input);
	white_spaces_skip(tokens);
	data->input = open((*tokens)->content, O_RDONLY);
	if (data->input == -1)
	{
		perror("minishell$>");
		g_exit_status = -2000;
	}
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
}

void	redirection_manage(t_data *data, t_token **tokens)
{
	if (finally_is_valid((*tokens)->type, 2))
		output_redirection(data, tokens);
	else if (finally_is_valid((*tokens)->type, 3))
		append(data, tokens);
	else if (finally_is_valid((*tokens)->type, 4))
		input_redirection(data, tokens);
	else if (finally_is_valid((*tokens)->type, 5))
	{
		if (data->input != -8)
			close(data->input);
		white_spaces_skip(tokens);
		data->std_int = dup(0);
		data->input = here_doc(data, tokens);
	}
}
