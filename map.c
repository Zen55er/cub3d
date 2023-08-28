/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:18:09 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/28 11:27:02 by gacorrei         ###   ########.fr       */
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

int	validate_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	i = skip_spaces(temp, i);
	if (temp[i] == 'N' && temp[i + 1] == 'O' && temp[i + 2] == ' ')
	{
		i += 2;
		i = skip_spaces(temp, i);
		if (data->n_path)
			return (print_error("Duplicate texture"));
		data->n_path = ft_substr(temp, i, ft_strlen(temp - i));
		if (access(data->n_path, R_OK))
			return (print_error("Invalid texture path"));
	}
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
			break ;
		if (validate_texture(data, temp))
		{
			free(temp);
			break ;
		}
		free(temp);
		temp = get_next_line(map_fd);
	}
}

int	copy_map(t_data *data, char *map_path)
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
	/*SKIP TEXTURE ELEMENTS*/
	
	
	while (1)
	{
		temp = get_next_line(map_fd);
		if (temp == -1)
			return (print_error("Failed while copying map"));
		if (!temp)
			break ;
		data->map_y++;
		line_size = ft_strlen(temp);
		if (line_size > data->map_x)
			data->map_x = line_size;
		free(temp);
		temp = get_next_line(map_fd);
	}
}

void	init_data(t_data *data)
{
	data->map = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->n_path = 0;
	data->s_path = 0;
	data->w_path = 0;
	data->e_path = 0;
	return ;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error("Usage: ./cub3d path_to_map"));
	init_data(&data);
	if (copy_map(&data, av[1]))
		return (free_all(&data));
}
