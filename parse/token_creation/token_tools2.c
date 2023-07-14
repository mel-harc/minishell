/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:25:44 by houadou           #+#    #+#             */
/*   Updated: 2023/06/21 15:23:48 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_strings(char *s1, char *s2, int flag)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ptr)
		exit(1);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	if (flag == 0)
		return (free(s1), free(s2), ptr);
	if (flag == 1)
		return (free(s1), ptr);
	if (flag == 2)
		return (free(s2), ptr);
	return (NULL);
}

static char	*create_string_with_char(char character)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		exit(1);
	str[0] = character;
	return (str);
}

char	*manage_string(int flag, char *s1, char *s2, char character)
{
	if (flag == 1)
		return (join_strings(s1, s2, 0));
	else if (flag == 2)
		return (create_string_with_char(character));
	else
		return (NULL);
}

int	check_conditions(char *line, int i)
{
	char	*special_chars;
	char	*white_spaces;
	char	next_char;

	special_chars = "~|@%^*{}[]><-.+=/";
	white_spaces = " \t\n";
	if (!line[i + 1])
		return (0);
	next_char = line[i + 1];
	if (ft_strchr(special_chars, next_char) != NULL)
		return (0);
	if (ft_strchr(white_spaces, next_char) != NULL)
		return (0);
	if (next_char == '"' || next_char == '$' || next_char == '\'')
		return (0);
	return (1);
}

int	check_quotes(char *line, t_data *data)
{
	int	i;

	i = -1;
	data->db_quotes = 0;
	data->sg_quotes = 0;
	while (line[++i])
	{
		if (line[i] == '"')
			data->db_quotes++;
		else if (line[i] == '\'')
			data->sg_quotes++;
		while (line[i] && line[i + 1] && (data->db_quotes || data->sg_quotes))
		{
			i++;
			if (line[i] == '"' && data->db_quotes)
				data->db_quotes--;
			else if (line[i] == '\'' && data->sg_quotes)
				data->sg_quotes--;
		}
	}
	if (data->db_quotes != 0 || data->sg_quotes != 0)
		return (write (2, "syntax error\n", 13), 0);
	return (1);
}
