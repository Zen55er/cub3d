/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:15:36 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/27 15:21:09 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->nswe_paths[0] = 0;
	data->nswe_paths[1] = 0;
	data->nswe_paths[2] = 0;
	data->nswe_paths[3] = 0;
	data->floor = -1;
	data->ceiling = -1;
	data->count = 0;
	data->map_start.x = 0;
	data->map_start.y = 0;
	data->key_states.w = 0;
	data->key_states.a = 0;
	data->key_states.s = 0;
	data->key_states.d = 0;
	data->key_states.l = 0;
	data->key_states.r = 0;
	init_data_2(data);
	return (0);
}

void	init_data_2(t_data *data)
{
	data->nswe_images[0].mlx_img = 0;
	data->nswe_images[1].mlx_img = 0;
	data->nswe_images[2].mlx_img = 0;
	data->nswe_images[3].mlx_img = 0;
	data->init = 0;
	data->window = 0;
	data->side = -1;
	data->image.mlx_img = 0;
	data->image.addr = 0;
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
	data.m_pos.x = data.map_start.x;
	data.m_pos.y = data.map_start.y;
	mlx(&data);
	mlx_destroy_image(data.init, data.image.mlx_img);
	mlx_destroy_window(data.init, data.window);
	free_all(&data);
}
