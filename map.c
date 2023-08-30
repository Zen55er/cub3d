/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:18:09 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/30 16:46:19 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	return (1);
}

int	skip_spaces(char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int	elements_ok(t_data *data)
{
	if (data->nswe_paths[0] && data->nswe_paths[1] && data->nswe_paths[2]
		&& data->nswe_paths[3] && data->floor && data->ceiling)
		return (1);
	return (0);
}

int	validate_elements(t_data *data, int map_fd)
{
	char	*temp;

	while (1)
	{
		temp = get_next_line(map_fd);
		if (temp == -1)
			return (print_error("Failed while reading map"));
		if (!temp)
			return (print_error("Missing texture elements"));
		data->count++;
		if (temp[0] != '\n' && validate_texture(data, temp))
		{
			free(temp);
			break ;
		}
		free(temp);
		if (elements_ok(data))
			break ;
	}
	return (0);
}

int	get_map_dimensions(t_data *data, int map_fd)
{
	char	*temp;
	int		flag;

	flag = 0;
	while (1)
	{
		temp = get_next_line(map_fd);
		if (temp == -1)
			return (print_error("Failed while reading map"));
		if (!temp)
			break ;
		if (temp[0] == '\n' && ft_free(temp) && data->count++)
		{
			if (!flag)
				continue ;
			return (print_error("Empty line on map"));
		}
		flag = 1;
		data->map_y++;
		if (ft_strlen(temp) > data->map_x)
			data->map_x = ft_strlen(temp);
		free(temp);
	}
	return (0);
}

int	get_map(t_data *data, int map_fd)
{
	char	*temp;
	int		i;

	i = -1;
	while (1)
	{
		temp = get_next_line(map_fd);
		if (temp == -1)
			return (print_error("Failed while reading map"));
		if (!temp)
			break ;
		if (data->count-- && ft_free(temp))
			continue ;
		data->map[++i] = temp;
	}
	return (0);
}

int	map(t_data *data, char *map_path)
{
	int		map_fd;
	char	*temp;
	int		line_size;

	if (access(map_path, F_OK))
		return (print_error("Map can't be accessed"));
	if (access(map_path, R_OK))
		return (print_error("Map does not have read permission"));
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
	//KEEP FROM HERE!!!!
}

void	init_data(t_data *data)
{
	data->map = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->nswe_paths[0] = 0;
	data->nswe_paths[1] = 0;
	data->nswe_paths[2] = 0;
	data->nswe_paths[3] = 0;
	data->floor = 0;
	data->ceiling = 0;
	data->count = 0;
	return ;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error("Usage: ./cub3d path_to_map"));
	init_data(&data);
	if (map(&data, av[1]))
		return (free_all(&data));
}
