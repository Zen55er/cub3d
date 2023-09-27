/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:27:08 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/27 15:31:09 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stepper(t_data *data, int flag)
{
	if (!flag)
	{
		data->side_dist.x += data->d_dist.x;
		data->m_pos.x += data->step.x;
	}
	else
	{
		data->side_dist.y += data->d_dist.y;
		data->m_pos.y += data->step.y;
	}
}

void	dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			stepper(data, 0);
			data->side = 0;
		}
		else
		{
			stepper(data, 1);
			data->side = 1;
		}
		if (data->map[data->m_pos.y][data->m_pos.x] == '1')
			hit = 1;
	}
	if (!data->side)
		data->perp_wall_dist = data->side_dist.x - data->d_dist.x;
	else
		data->perp_wall_dist = data->side_dist.y - data->d_dist.y;
}

void	post_dda(t_data *data)
{
	data->line_height = (int)(WINDOW_HEIGHT / data->perp_wall_dist);
	data->draw_start = (WINDOW_HEIGHT - data->line_height) / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = (WINDOW_HEIGHT + data->line_height) / 2;
	if (data->draw_end >= WINDOW_HEIGHT)
		data->draw_end = WINDOW_HEIGHT;
}

int	choose_texture(t_data *data)
{
	if (data->side)
	{
		if ((double)data->m_pos.y - data->pos.y > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if ((double)data->m_pos.x - data->pos.x > 0)
			return (2);
		else
			return (3);
	}
}

void	calc_textures(t_data *data, int i)
{
	t_coord	tex;
	double	wall_x;
	double	step;
	double	tex_pos;

	if (!data->side)
		wall_x = data->pos.y + data->perp_wall_dist * data->ray_dir.y;
	else
		wall_x = data->pos.x + data->perp_wall_dist * data->ray_dir.x;
	wall_x -= floor(wall_x);
	tex.x = (int)(wall_x * (double)TEXTURE_W_H);
	if ((!data->side && data->ray_dir.x < 0)
		|| (data->side && data->ray_dir.y > 0))
		tex.x = TEXTURE_W_H - tex.x - 1;
	step = 1.0 * TEXTURE_W_H / data->line_height;
	tex_pos = (data->draw_start + (data->line_height - WINDOW_HEIGHT) / 2)
		* step;
	set_colour(data, tex, (t_coord_d){tex_pos, step}, i);
}
