/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:44:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/02/01 09:01:05 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_free(char *line)
{
	free(line);
	return (0);
}

static int	fix_buffer(char *buffer)
{
	int	i;
	int	j;
	int	nl;

	i = 0;
	j = 0;
	nl = 0;
	while (buffer && buffer[i])
	{
		if (nl == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			nl = 1;
		buffer[i] = 0;
		i++;
	}
	return (nl);
}

char	*get_next_line_bonus(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			buf;

	if (fd > FOPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_strjoin(0, buffer[fd]);
	if (fix_buffer(buffer[fd]))
		return (line);
	buf = 1;
	while (buf > 0)
	{
		buf = read(fd, buffer[fd], BUFFER_SIZE);
		if (buf == -1)
			return (ft_free(line));
		if (buf == 0 && line[0] == '\0')
			return (ft_free(line));
		line = ft_strjoin(line, buffer[fd]);
		if (fix_buffer(buffer[fd]))
			break ;
	}
	return (line);
}
