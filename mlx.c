/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:57:13 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/05 13:20:14 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Handles no event cases*/
int	no_event(t_data *data)
{
	(void)data;
	return (0);
}

/*Frees window*/
int	close_window(t_data *data)
{
	mlx_destroy_window(data->init, data->window);
	return (0);
}

/*Begins movement and turning logic*/
int	key_release(int key, t_data *data)
{
	if (key == XK_Escape)
		close_window(data);
	else if (key == XK_w)
		printf("W\n");
	else if (key == XK_s)
		printf("S\n");
	else if (key == XK_a)
		printf("A\n");
	else if (key == XK_d)
		printf("D\n");
	else if (key == XK_Left)
		printf("LEFT\n");
	else if (key == XK_Right)
		printf("RIGHT\n");
	return (0);
}

/*Copies images to memory*/
int	open_images(t_data *data)
{
	int	i;
	int	size;

	size = 360;
	i = -1;
	data->nswe_images = (void **)malloc(sizeof(void *) * 5);
	data->nswe_images[4] = 0;
	while (++i < 4)
		data->nswe_images[i] = mlx_xpm_file_to_image(data->init,
				data->nswe_paths[i], &size, &size);
	return (0);
}

/*Creates mlx loops for game to run*/
int	mlx(t_data *data)
{
	data->init = mlx_init();
	if (!data->init)
		return (print_error("mlx failed"));
	data->window = mlx_new_window(data->init, 1600, 900, "cub3D");
	if (!data->window)
		return (print_error("mlx window failed"));
	if (open_images(data))
		return (print_error("mlx failed trying to open images"));
	mlx_loop_hook(data->init, no_event, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_release, data);
	mlx_hook(data->window, DestroyNotify, KeyPressMask, close_window, data);
	mlx_loop(data->init);
	return (0);
}
