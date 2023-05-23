/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:22:05 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/22 18:50:23 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// char	*cmd_line;
	t_data	data;
	(void)argc;
	(void)argv;

	fill_env(envp, &data);
	// while (1)
	// {
	// 	cmd_line = readline("BACH >> ");
	// 	execmds(cmd_line, data.env);
	// }
	return (0);
}