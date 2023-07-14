/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:28:37 by houadou           #+#    #+#             */
/*   Updated: 2023/07/08 22:30:12 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_exp(char **env, t_data *data)
{
	int		i;
	char	**tab;
	char	*pwd;

	data->ev = NULL;
	i = 0;
	if (!*env)
	{
		pwd = getcwd(NULL, 0);
		create_and_addback_env_node(&data->ev, "PWD", pwd);
		create_and_addback_env_node(&data->ev, "SHLVL", "1");
		create_and_addback_env_node(&data->ev, "_", "/usr/bin/env");
		_set_path(data);
		return (free(pwd));
	}
	while (env[i])
	{
		tab = ft_split(env[i], '=');
		create_and_addback_env_node(&data->ev, tab[0], tab[1]);
		free_tab(tab);
		i++;
	}
}

static void	fill_env(t_data *data, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_env_exp(env, data);
}

static void	start_loop(t_data *data)
{
	char	*line;

	while (1)
	{
		rl_catch_signals = 0;
		signal_handler();
		line = readline("minishell$> ");
		if (!line)
			return (ft_putstr_fd("exit\n", 1));
		if (!line && g_exit_status == 1)
		{
			g_exit_status = 0;
			continue ;
		}
		line = trim(&line, 1);
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		start_token(line, data);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	fill_env(data, ac, av, env);
	start_loop(data);
	free_env(&data->ev);
	free(data);
}
