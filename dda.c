/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:31:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/27 15:32:07 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(t_img2 img, int i, int j)
{
	return (j * (img.line_len / 4) + i);
}

void	set_coord(t_coord_d *coord, double x, double y)
{
	coord->x = x;
	coord->y = y;
	return ;
}

void	get_start_dir(t_data *data)
{
	if (data->map[(int)data->pos.y][(int)data->pos.x] == 'N')
	{
		set_coord(&data->direction, 0, -1);
		set_coord(&data->camera, FOV_FACTOR, 0);
	}
	else if (data->map[(int)data->pos.y][(int)data->pos.x] == 'S')
	{
		set_coord(&data->direction, 0, 1);
		set_coord(&data->camera, -FOV_FACTOR, 0);
	}
	else if (data->map[(int)data->pos.y][(int)data->pos.x] == 'W')
	{
		set_coord(&data->direction, -1, 0);
		set_coord(&data->camera, 0, -FOV_FACTOR);
	}
	else
	{
		set_coord(&data->direction, 1, 0);
		set_coord(&data->camera, 0, FOV_FACTOR);
	}
	return ;
}

void	step_dist(t_data *data)
{
	if (data->ray_dir.x < 0)
	{
		data->step.x = -1;
		data->side_dist.x = (data->pos.x - data->m_pos.x) * data->d_dist.x;
	}
	else
	{
		data->step.x = 1;
		data->side_dist.x = (data->m_pos.x + 1 - data->pos.x) * data->d_dist.x;
	}
	if (data->ray_dir.y < 0)
	{
		data->step.y = -1;
		data->side_dist.y = (data->pos.y - data->m_pos.y) * data->d_dist.y;
	}
	else
	{
		data->step.y = 1;
		data->side_dist.y = (data->m_pos.y + 1 - data->pos.y) * data->d_dist.y;
	}
}

void	pre_dda(t_data *data)
{
	int	i;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		data->cam_x = 2 * i / (double)WINDOW_WIDTH - 1;
		data->ray_dir.x = data->direction.x + (data->camera.x * data->cam_x);
		data->ray_dir.y = data->direction.y + (data->camera.y * data->cam_x);
		data->m_pos.x = (int)data->pos.x;
		data->m_pos.y = (int)data->pos.y;
		if (data->ray_dir.x != 0)
			data->d_dist.x = fabs(1 / data->ray_dir.x);
		else
			data->d_dist.x = pow(10, 30);
		if (data->ray_dir.y != 0)
			data->d_dist.y = fabs(1 / data->ray_dir.y);
		else
			data->d_dist.y = pow(10, 30);
		step_dist(data);
		dda(data);
		post_dda(data);
		calc_textures(data, i);
	}
}
