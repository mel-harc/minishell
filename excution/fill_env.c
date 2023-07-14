/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:45:03 by mel-harc          #+#    #+#             */
/*   Updated: 2023/07/10 10:50:07 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**_env(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	char	*str;
	int		i;

	tmp = env;
	envp = (char **)malloc(sizeof(char *) * (size_of_var(tmp) + 1));
	if (!envp)
		exit(1);
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			str = _strjoin(tmp->variable, "=");
			envp[i] = _strjoin(str, tmp->value);
			free(str);
		}
		else
			envp[i] = tmp->variable;
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	size_of_var(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	_redirect(t_command *cmd)
{
	if (g_exit_status == -2000 || cmd->input == -1 || cmd->output == -1)
		exit(1);
	if (cmd->input > 0)
	{
		dup2(cmd->input, 0);
		close(cmd->input);
	}
	if (cmd->output > 0)
	{
		dup2(cmd->output, 1);
		close(cmd->output);
	}
}

void	free_paths(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	_set_path(t_data *data)
{
	char	*path;
	t_env	*node;
	char	*save;

	path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	create_and_addback_env_node(&data->ev, "PATH", path);
	node = _is_exist(data, "PATH");
	if (node)
	{
		save = node->declare;
		node->declare = ft_strdup("not printed");
		free(save);
	}
}
