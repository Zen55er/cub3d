/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:31:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/14 16:14:06 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_coord(t_coord *coord, int x, int y)
{
	coord->x = x;
	coord->y = y;
	return ;
}

void	get_start_dir(t_data *data)
{
	if (data->map[data->map_start.y][data->map_start.x] == 'N')
	{
		set_coord(&data->direction, 0, -1);
		set_coord(&data->camera, FOV_FACTOR, 0);
	}
	else if (data->map[data->map_start.y][data->map_start.x] == 'S')
	{
		set_coord(&data->direction, 0, 1);
		set_coord(&data->camera, -FOV_FACTOR, 0);
	}
	else if (data->map[data->map_start.y][data->map_start.x] == 'W')
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

void	fov(t_data *data)
{
	data->fov = 2 * atan(FOV_FACTOR / 1.0);
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

int	pre_dda(t_data *data)
{
	int	i;

	get_start_dir(data);
	fov(data);
	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		data->cam_x = 2 * i / WINDOW_WIDTH - 1;
		data->ray_dir.x = data->direction.x + (data->camera.x * data->cam_x);
		data->ray_dir.y = data->direction.y + (data->camera.y * data->cam_x);
		data->m_pos.x = (int)data->pos.x;
		data->m_pos.y = (int)data->pos.y;
		if (data->ray_dir.x != 0)
			data->d_dist.x = abs(1 / data->ray_dir.x);
		else
			data->d_dist.x = pow(10, 30);
		if (data->ray_dir.y != 0)
			data->d_dist.y = abs(1 / data->ray_dir.y);
		else
			data->d_dist.y = pow(10, 30);
		step_dist(data);
	}
}

void	stepper(tdata *data, int flag)
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
	int	side;

	hit = 0;
	side = -1;
	while (!hit)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			stepper(data, 0);
			side = 0;
		}
		else
		{
			stepper(data, 1);
			side = 1;
		}
		if (data->map[data->m_pos.y][data->m_pos.x] == 1)
			hit = 1;
	}
	if (!side)
		data->perp_wall_dist = data->side_dist.x - data->d_dist.x;
	else
		data->perp_wall_dist = data->side_dist.y - data->d_dist.y;
}

void	post_dda(t_data *data)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	// int	pitch; TEST

	line_height = (int)(WINDOW_HEIGHT / data->perp_wall_dist);
	draw_start = (WINDOW_HEIGHT - line_height) / 2 /* + pitch */;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WINDOW_HEIGHT + line_height) / 2 /* + pitch */;
	if (draw_end < 0)
		draw_end = WINDOW_HEIGHT - 1;
}

void	calc_textures(t_data *data)
{
	int		tex_num;
	t_coord	tex;
	double	wall_x;
	double	step;
	double	tex_pos;

	
}
