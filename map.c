/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:18:09 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/04 09:16:24 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_forbidden(char *temp)
{
	int	i;

	i = -1;
	while (temp[++i])
		if (temp[i] != '0' && temp[i] != '1' && temp[i] != 'N' && temp[i] != 'S'
			&& temp[i] != 'W' && temp[i] != 'E' && temp[i] != ' ')
			return (print_error("Found extra element or forbidden character"));
	return (0);
}

int	get_map_dimensions(t_data *data, int map_fd)
{
	char	*temp;
	int		flag;

	flag = 0;
	while (1)
	{
		temp = gnl(map_fd);
		if (!temp)
			break ;
		if (!temp[0] && ft_free(temp) && data->count++)
		{
			if (!flag)
				continue ;
			return (print_error("Empty line on map"));
		}
		else if (check_forbidden(temp) && ft_free(temp))
			return (1);
		flag = 1;
		if (++data->map_y && (int)ft_strlen(temp) > data->map_x)
			data->map_x = ft_strlen(temp);
		free(temp);
	}
	if (!data->map_x)
		return (print_error("Map not found"));
	return (0);
}

int	get_map(t_data *data, int map_fd)
{
	char	*temp;
	int		i;

	i = -1;
	while (1)
	{
		temp = gnl(map_fd);
		if (!temp)
			break ;
		if (data->count-- > 0 && ft_free(temp))
			continue ;
		data->map[++i] = temp;
	}
	return (0);
}

int	map(t_data *data, char *map_path)
{
	int		map_fd;

	if (access(map_path, F_OK))
		return (print_error("Map can't be accessed"));
	if (access(map_path, R_OK))
		return (print_error("Map does not have read permission"));
	if (ft_strcmp((map_path + (ft_strlen(map_path) - 4)), ".cub"))
		return (print_error("Map needs to have .cub file name extension"));
	map_fd = open(map_path, O_RDONLY, 0644);
	if (map_fd == -1)
		return (print_error("Failed to open map"));
	if (validate_elements(data, map_fd))
		return (1);
	if (get_map_dimensions(data, map_fd))
		return (1);
	close(map_fd);
	map_fd = open(map_path, O_RDONLY, 0644);
	data->map = (char **)malloc(sizeof(char *) * (data->map_y + 1));
	data->map[data->map_y] = 0;
	if (get_map(data, map_fd))
		return (1);
	close(map_fd);
	if (validate_map(data))
		return (1);
	return (0);
}
