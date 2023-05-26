/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:22:05 by mel-harc          #+#    #+#             */
/*   Updated: 2023/05/24 22:50:18 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_data	data;
	(void)argc;
	(void)argv;

	fill_env(envp, &data);
	while (1)
	{
		cmd_line = readline("BASH >> ");
		fill_cmds(cmd_line, &data);
		execmds(&data, envp);
	}
	return (0);
}