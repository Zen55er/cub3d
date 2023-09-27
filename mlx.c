/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:57:13 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/27 15:25:03 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Frees window*/
int	close_window(t_data *data)
{
	mlx_loop_end(data->init);
	return (0);
}

/*Begins movement and turning logic*/
int	key_press(int key, t_data *data)
{
	if (key == XK_Escape)
		close_window(data);
	if (key == XK_w)
		data->key_states.w = 1;
	if (key == XK_s)
		data->key_states.s = 1;
	if (key == XK_a)
		data->key_states.a = 1;
	if (key == XK_d)
		data->key_states.d = 1;
	if (key == XK_Left)
		data->key_states.l = 1;
	if (key == XK_Right)
		data->key_states.r = 1;
	movement(data);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_w)
		data->key_states.w = 0;
	if (key == XK_s)
		data->key_states.s = 0;
	if (key == XK_a)
		data->key_states.a = 0;
	if (key == XK_d)
		data->key_states.d = 0;
	if (key == XK_Left)
		data->key_states.l = 0;
	if (key == XK_Right)
		data->key_states.r = 0;
	movement(data);
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
	data->window = mlx_new_window(data->init, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (!data->window)
		return (print_error("mlx window failed"));
	if (open_images(data))
		return (1);
	get_start_dir(data);
	mlx_mouse_move(data->init, data->window, WINDOW_WIDTH / 2,
		WINDOW_HEIGHT / 2);
	mlx_mouse_hide(data->init, data->window);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->window, MotionNotify, PointerMotionMask, mouse_look, data);
	mlx_hook(data->window, DestroyNotify, KeyPressMask, close_window, data);
	mlx_loop_hook(data->init, big_loop, data);
	mlx_loop(data->init);
	return (0);
}
