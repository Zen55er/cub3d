/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:57:13 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/18 10:54:56 by gacorrei         ###   ########.fr       */
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

void	copy_pixels(int *buffer, t_img2 image)
{
	int	x;
	int	y;

	y = -1;
	while (++y < TEXTURE_W_H)
	{
		x = -1;
		while (++x < TEXTURE_W_H)
			buffer[y * TEXTURE_W_H + x]
				= image.addr[y * TEXTURE_W_H + x];
	}
}

/*Copies images to memory*/
int	open_images(t_data *data)
{
	int		i;
	int		size;
	t_img2	temp;

	size = 360;
	i = -1;
	data->nswe_images = (int **)malloc(sizeof(int *) * 5);
	data->nswe_images[4] = 0;
	while (++i < 4)
	{
		temp.mlx_img = mlx_xpm_file_to_image(data->init,
				data->nswe_paths[i], &size, &size);
		if (!temp.mlx_img)
			return (1);
		temp.addr = (int *)mlx_get_data_addr(temp.mlx_img, &temp.bpp,
				&temp.line_len, &temp.endian);
		copy_pixels(data->nswe_images[i], temp);
		mlx_destroy_image(data->init, temp.mlx_img);
	}
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
		return (print_error("invalid xmp file"));
	mlx_loop_hook(data->init, no_event, data);
	mlx_loop_hook(data->init, big_loop, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_release, data);
	mlx_hook(data->window, DestroyNotify, KeyPressMask, close_window, data);
	mlx_loop(data->init);
	return (0);
}
