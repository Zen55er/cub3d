/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:23:14 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/27 15:24:27 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	update_mouse_pos(int x, int y, t_data *data)
{
	x = WINDOW_WIDTH / 2;
	mlx_mouse_move(data->init, data->window, x, y);
}

int	mouse_look(int x, int y, t_data *data)
{
	static int	old_pos;

	old_pos = WINDOW_WIDTH / 2;
	if (x == old_pos)
		return (0);
	if (x < old_pos)
		rotate(data, -(ROTATION / 4.0));
	else if (x > old_pos)
		rotate(data, (ROTATION / 4.0));
	old_pos = x;
	update_mouse_pos(x, y, data);
	return (0);
}
