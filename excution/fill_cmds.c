/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:47:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/06/06 15:47:12 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    fill_cmds(char *cmd_line, t_data *data)
{
    char **split_cmds;
    int     i;

    data->head_cmds = NULL;
    split_cmds = ft_split(cmd_line, '|');
    if (!split_cmds)
        return ;
    i = -1;
    while (split_cmds[++i])
    {
        if (lst_add_cmd(data, new_cmd(split_cmds[i])))
            return ;
    }
    return ;
}

t_list_cmds    *new_cmd(char *cmd)
{
    t_list_cmds *node;

    node = (t_list_cmds *)malloc(sizeof(t_list_cmds));
    if (!node)
        return (NULL);
    node->cmd = ft_split(cmd, ' ');
    node->next = NULL;
    node->previous = NULL;
    return (node);
}

int lst_add_cmd(t_data *data, t_list_cmds *new_cmd)
{
    t_list_cmds *tmp;

    tmp = NULL;
    if (!new_cmd)
        return (1);
    if (!data->head_cmds)
        data->head_cmds = new_cmd;
    else
    {
        tmp = data->head_cmds;
        while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
        new_cmd->previous = tmp;
    }
    return (0);
}