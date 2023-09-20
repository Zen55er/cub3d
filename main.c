/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:15:36 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/20 08:47:48 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	/*FOR DEBUGGING ONLY, DELETE AT THE END*/
	i = -1;
	while (map[++i])
		printf(":%s:\n", map[i]);
	printf("\n");
	return ;
}

/*Prints error messages according to subject*/
int	print_error(char *message)
{
	printf("Error\n%s\n", message);
	return (1);
}

/*Initializes data members*/
int	init_data(t_data *data)
{
	data->map = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->nswe_images = (int **)ft_calloc(sizeof(int *), 5);
	if (!data->nswe_images)
		return (print_error("failed texture allocation"));
	data->nswe_paths[0] = 0;
	data->nswe_paths[1] = 0;
	data->nswe_paths[2] = 0;
	data->nswe_paths[3] = 0;
	data->floor = -1;
	data->ceiling = -1;
	data->count = 0;
	data->map_start.x = 0;
	data->map_start.y = 0;
	data->init = 0;
	data->window = 0;
	data->side = -1;
	data->buffer = (int **)ft_calloc(sizeof(int *), WINDOW_HEIGHT + 1);
	for (int y = 0; y < WINDOW_HEIGHT; y++)
		data->buffer[y] = (int *)ft_calloc(sizeof(int), WINDOW_WIDTH + 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error("Usage: ./cub3d path_to_map"));
	if (init_data(&data))
		return (free_all(&data));
	if (map(&data, av[1]))
		return (free_all(&data));
	data.pos.x = (double)data.map_start.x + 0.5;
	data.pos.y = (double)data.map_start.y + 0.5;
	print_map(data.map);
	// mlx(&data);
	free_all(&data);
}
