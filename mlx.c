/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:57:13 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/22 12:10:39 by gacorrei         ###   ########.fr       */
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
	mlx_loop_end(data->init);
	return (0);
}

/*Begins movement and turning logic*/
int	key_release(int key, t_data *data)
{
	// printf("BEFORE MOVE: pos_x: %lf, pos_y: %lf\nmap_pos_x: %i, map_pos_y: %i\n", data->pos.x, data->pos.y, data->m_pos.x, data->m_pos.y);
	if (key == XK_Escape)
		close_window(data);
	else if (key == XK_w)
		move(data, 1, 1);
	else if (key == XK_s)
		move(data, -1, 1);
	else if (key == XK_a)
		move(data, -1, 0);
	else if (key == XK_d)
		move(data, 1, 0);
	else if (key == XK_Left)
		rotate(data, -1);
	else if (key == XK_Right)
		rotate(data, 1);
	// printf("AFTER MOVE: pos_x: %lf, pos_y: %lf\nmap_pos_x: %i, map_pos_y: %i\n", data->pos.x, data->pos.y, data->m_pos.x, data->m_pos.y);
	return (0);
}

int	init_image(t_data *data)
{
	data->image.mlx_img = mlx_new_image(data->init,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->image.mlx_img)
		return (1);
	data->image.addr = (int *)mlx_get_data_addr(data->image.mlx_img,
			&data->image.bpp, &data->image.line_len, &data->image.endian);
	if (!data->image.addr)
		return (1);
	return (0);
}

int	open_images(t_data *data)
{
	int		i;
	int		size;

	size = TEXTURE_W_H;
	i = -1;
	while (++i < 4)
	{
		data->nswe_images[i].mlx_img = mlx_xpm_file_to_image(data->init,
				data->nswe_paths[i], &size, &size);
		if (!data->nswe_images[i].mlx_img)
			return (print_error("failed image allocation"));
		data->nswe_images[i].addr = \
			(int *)mlx_get_data_addr(data->nswe_images[i].mlx_img,
				&data->nswe_images[i].bpp, &data->nswe_images[i].line_len,
				&data->nswe_images[i].endian);
		if (!data->nswe_images[i].addr)
			return (print_error("failed image allocation"));
	}
	init_image(data);
	return (0);
}

/*Creates mlx loops for game to run*/
int	mlx(t_data *data)
{
	data->init = mlx_init();
	if (!data->init)
		return (print_error("mlx failed"));
	data->window = mlx_new_window(data->init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!data->window)
		return (print_error("mlx window failed"));
	if (open_images(data))
		return (1);
	get_start_dir(data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_release, data);
	mlx_hook(data->window, DestroyNotify, KeyPressMask, close_window, data);
	mlx_loop_hook(data->init, big_loop, data);
	mlx_loop(data->init);
	return (0);
}
