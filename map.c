/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:18:09 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/01 09:46:00 by gacorrei         ###   ########.fr       */
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
		&& data->nswe_paths[3] && data->floor >= 0 && data->ceiling >= 0)
		return (1);
	return (0);
}

int	validate_elements(t_data *data, int map_fd)
{
	char	*temp;

	while (1)
	{
		temp = gnl(map_fd);
		if (!temp)
			return (print_error("Missing texture elements"));
		data->count++;
		if (temp[0] != 0 && validate_texture(data, temp))
		{
			free(temp);
			return (1);
		}
		free(temp);
		if (elements_ok(data))
			break ;
	}
	return (0);
}

int	forbidden(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'W' && c != 'E' && c != ' ')
		return (1);
	return (0);
}

int	check_forbidden(char *temp)
{
	int	i;

	i = -1;
	while (temp[++i])
		if (forbidden(temp[i]))
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

char	*add_spaces(char *str, int len)
{
	char	*temp;
	int		i;

	temp = ft_strjoin_free(str, ft_strdup(" "));
	i = -1;
	while (++i < len - 1)
		temp = ft_strjoin_free(temp, ft_strdup(" "));
	return (temp);
}

void	fill_edges(t_data *data)
{
	int		i;
	int		len;

	i = -1;
	while (data->map[++i])
	{
		len = data->map_x - ft_strlen(data->map[i]);
		if (len)
			data->map[i] = add_spaces(data->map[i], len);
	}
	return ;
}

void	update_start(t_data *data, int x, int y)
{
	data->map_start.x = x;
	data->map_start.y = y;
	return ;
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	fill_edges(data);
	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (!start && (data->map[j][i] == 'N' || data->map[j][i] == 'S'
				|| data->map[j][i] == 'W' || data->map[j][i] == 'E') && ++start)
				update_start(data, i, j);
			else if (start && (data->map[j][i] == 'N' || data->map[j][i] == 'S'
				|| data->map[j][i] == 'W' || data->map[j][i] == 'E'))
				return (print_error("Found duplicate start position"));
		}
	}
	if (!data->map_start.x)
		return (print_error("Start position missing"));
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

void	init_data(t_data *data)
{
	data->map = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->nswe_paths[0] = 0;
	data->nswe_paths[1] = 0;
	data->nswe_paths[2] = 0;
	data->nswe_paths[3] = 0;
	data->floor = -1;
	data->ceiling = -1;
	data->count = 0;
	data->map_start.x = 0;
	data->map_start.y = 0;
	return ;
}

void	print_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		printf(":%s:\n", map[i]);
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
	print_map(data.map);
	free_all(&data);
}
