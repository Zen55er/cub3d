/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:50:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/27 14:57:53 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_minimap(t_data *data)
{
	t_coord	px;
	int		size;
	double	p;

	p = (double)(WINDOW_HEIGHT) / (double)(WINDOW_WIDTH);
	size = (WINDOW_WIDTH / 4) * p;
	reset_minimap(data);
	get_minimap(data);
	px.y = -1;
	while (++px.y < MM_SIZE)
	{
		px.x = -1;
		while (++px.x < MM_SIZE)
			draw_square(data, px.x * PPT,
				((WINDOW_HEIGHT - size) + (px.y * PPT)),
				data->mini_map[px.y][px.x]);
	}
	return (0);
}

int	draw_square(t_data *data, int i, int j, int c)
{
	int	k;
	int	l;

	l = -1;
	while (++l < PPT)
	{
		k = -1;
		while (++k < PPT)
			data->image.addr[get_pixel(data->image, (i + k), (j + l))] = c;
	}
	return (0);
}

/* 2 = player | 1 = wall | 3 = floor | O = out of bounds */
void	get_minimap(t_data *data)
{
	t_coord	index;
	t_coord	real_pos;
	t_coord	temp;

	real_pos.x = data->m_pos.x;
	real_pos.y = data->m_pos.y;
	index.y = (MM_SIZE / 2);
	while (index.y && real_pos.y)
	{
		index.y--;
		real_pos.y--;
	}
	index.x = (MM_SIZE / 2);
	while (index.x && real_pos.x)
	{
		index.x--;
		real_pos.x--;
	}
	temp.x = index.x;
	temp.y = real_pos.x;
	while (index.y < MM_SIZE)
	{
		real_pos.x = temp.y;
		index.x = temp.x;
		while (index.x < MM_SIZE)
		{
			put_color(data, index, real_pos);
			real_pos.x++;
			index.x++;
		}
		index.y++;
		real_pos.y++;
	}
}

void	put_color(t_data *data, t_coord spot, t_coord pos)
{
	if (pos.y < data->map_y && pos.x < data->map_x)
	{
		if (spot.x == (MM_SIZE / 2) && spot.y == (MM_SIZE / 2))
			data->mini_map[spot.y][spot.x] = 0x95C623;
		else if (data->map[pos.y][pos.x] == '1')
			data->mini_map[spot.y][spot.x] = 0x5E5E5E;
		else if (data->map[pos.y][pos.x] == '0'
			|| data->map[pos.y][pos.x] == 'N' || data->map[pos.y][pos.x] == 'S'
			|| data->map[pos.y][pos.x] == 'W' || data->map[pos.y][pos.x] == 'E')
			data->mini_map[spot.y][spot.x] = 0xDEDEDE;
	}
	return ;
}

void	reset_minimap(t_data *data)
{
	t_coord	spot;

	spot.y = -1;
	while (++spot.y < MM_SIZE)
	{
		spot.x = -1;
		while (++spot.x < MM_SIZE)
			data->mini_map[spot.y][spot.x] = 0xC4C4C4;
	}
}
