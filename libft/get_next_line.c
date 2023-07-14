/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houadou <houadou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:29:25 by houadou           #+#    #+#             */
/*   Updated: 2023/06/16 16:33:30 by houadou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*rtn_l(char	*ln)
{
	int		i;
	char	*l;

	if (!*ln)
		return (NULL);
	i = 0;
	while (ln[i] && ln[i] != '\n')
		i++;
	if (ln[i] == '\0')
		l = (char *)malloc(i + 1);
	else
		l = (char *)malloc(i + 2);
	i = -1;
	while (ln[++i] && ln[i] != '\n')
		l[i] = ln[i];
	if (ln[i] == '\n')
		l[i++] = '\n';
	l[i] = 0;
	return (l);
}

static char	*rtn_p(char	*pos)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	while (pos[i] && pos[i] != '\n')
		i++;
	if (!pos[i])
		return (free(pos), NULL);
	p = (char *)malloc(gnl_strlen(pos) - i + 1);
	if (!p)
		return (NULL);
	j = 0;
	while (pos[++i])
		p[j++] = pos[i];
	p[j] = 0;
	return (free(pos), p);
}

char	*get_next_line(int fd)
{
	int			rd;
	char		*line;
	char		*buffer;
	static char	*position;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rd = 1;
	while (ft_new_line(position) && rd)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (buffer[0] == '\n')
			return (free(buffer), ft_strdup(""));
		if (rd == -1)
			return (free(buffer), NULL);
		buffer[rd] = 0;
		position = gnl_strjoin(position, buffer);
	}
	line = rtn_l(position);
	return (position = rtn_p(position), free(buffer), line);
}
