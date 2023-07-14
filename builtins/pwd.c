/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:49:06 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/23 22:40:00 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_pwd(t_data *data)
{
	char	*pwd;
	t_env	*node;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		node = _is_exist(data, "PWD");
		if (node)
			printf("%s\n", node->value);
		return ;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
}
