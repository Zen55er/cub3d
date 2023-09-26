/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:31:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/26 14:28:08 by tlemos-m         ###   ########.fr       */
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
	int		j;
	int		tex_num;
	t_coord	tex;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		colour;

	tex_num = choose_texture(data);
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
	tex_pos = (data->draw_start + (data->line_height - WINDOW_HEIGHT) / 2) * step;
	j = data->draw_start;
	while (j < data->draw_end)
	{
		if (tex_pos > (double)INT_MAX)
			tex.y = INT_MAX;
		else
			tex.y = (int)tex_pos /* & (TEXTURE_W_H - 1) */;
		tex_pos += step;
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
	mlx_put_image_to_window(data->init, data->window,
		data->image.mlx_img, 0, 0);
	data->m_pos.x = (int)data->pos.x;
	data->m_pos.y = (int)data->pos.y;
	mini_map(data);
	mlx_put_image_to_window(data->init, data->window,
		data->image.mlx_img, 0, 0);
	return (0);
}
