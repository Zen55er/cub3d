/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:38:20 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/31 15:42:32 by gacorrei         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			buf;

	if (fd > FOPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_strjoin2(0, buffer);
	if (fix_buffer(buffer))
		return (line);
	buf = 1;
	while (buf > 0)
	{
		buf = read(fd, buffer, BUFFER_SIZE);
		if (buf == -1)
			return (ft_free(line));
		if (buf == 0 && line[0] == '\0')
			return (ft_free(line));
		line = ft_strjoin2(line, buffer);
		if (fix_buffer(buffer))
			break ;
	}
	return (line);
}

char	*remove_nl(char *str)
{
	char	*temp;

	if (str[ft_strlen(str) - 1] != '\n')
		return (str);
	temp = ft_substr(str, 0, ft_strlen(str) - 1);
	free (str);
	return (temp);
}

char	*gnl(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			buf;

	if (fd > FOPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_strjoin2(0, buffer);
	if (fix_buffer(buffer))
		return (remove_nl(line));
	buf = 1;
	while (buf > 0)
	{
		buf = read(fd, buffer, BUFFER_SIZE);
		if (buf == -1)
			return (ft_free(line));
		if (buf == 0 && line[0] == '\0')
			return (ft_free(line));
		line = ft_strjoin2(line, buffer);
		if (fix_buffer(buffer))
			break ;
	}
	return (remove_nl(line));
}
