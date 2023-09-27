/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:27:25 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/27 15:30:52 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_colour(t_data *data, t_coord tex, t_coord_d pos_step, int i)
{
	int	colour;
	int	j;
	int	tex_num;

	tex_num = choose_texture(data);
	j = data->draw_start;
	while (j < data->draw_end)
	{
		if (pos_step.x > (double)INT_MAX)
			tex.y = INT_MAX;
		else
			tex.y = (int)pos_step.x;
		pos_step.x += pos_step.y;
		colour = data->nswe_images[tex_num].addr[TEXTURE_W_H * tex.y + tex.x];
		if (!colour)
			colour++;
		data->image.addr[get_pixel(data->image, i, j)] = colour;
		j++;
	}
}

void	draw_ceiling_floor(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		i = -1;
		while (++i < WINDOW_WIDTH)
		{
			if (j < (WINDOW_HEIGHT / 2))
				data->image.addr[get_pixel(data->image, i, j)] = data->ceiling;
			else
				data->image.addr[get_pixel(data->image, i, j)] = data->floor;
		}
	}
}

int	big_loop(t_data *data)
{
	draw_ceiling_floor(data);
	pre_dda(data);
	data->m_pos.x = (int)data->pos.x;
	data->m_pos.y = (int)data->pos.y;
	render_minimap(data);
	mlx_put_image_to_window(data->init, data->window,
		data->image.mlx_img, 0, 0);
	return (0);
}
