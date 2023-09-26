/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:50:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/26 15:47:30 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mini_map(t_data *data)
{
	t_coord	px;
	int		size;
	int		flag;
	double	p;

	p = (double)(WINDOW_HEIGHT) / (double)(WINDOW_WIDTH);
	size = (WINDOW_WIDTH / 4) * p;
	get_minimap(data, 9);
	px.y = -1;
	flag = 1;
	while (++px.y < MM_SIZE)
	{
		px.x = -1;
		while (++px.x < MM_SIZE)
			draw_square(data, px.x * PPT, (WINDOW_HEIGHT - size) + (px.y * PPT), data->mini_map[px.y][px.x]);
		flag++;
	}
	return (0);
}

int	draw_square(t_data *data, int i, int j, int flag)
{
	int	k;
	int	l;

	l = -1;
	(void)flag;
	while (++l < PPT)
	{
		k = -1;
		while (++k < PPT)
			data->image.addr[get_pixel(data->image, (i + k), (j + l))] = flag;
	}
	return (0);
}

/* 2 = player | 1 = wall | 3 = floor | O = out of bounds */
void	get_minimap(t_data *data, int size)
{
	t_coord	index;
	t_coord	real_pos;

	real_pos.x = data->m_pos.x;
	real_pos.y = data->m_pos.y;
	index.y = size / 2;
	while (--index.y && --real_pos.y)
	{
		index.x = size / 2;
		while (--index.x && --real_pos.x)
			continue ;
	}
	while (index.y < size && real_pos.y < data->map_y)
	{
		while (index.x < size && real_pos.x < data->map_x)
		{
			if (index.x == size / 2 && index.y == size / 2)
				data->mini_map[index.y][index.x] = 0x00FF00;
			else if (data->map[real_pos.y][real_pos.x] == '1')
				data->mini_map[index.y][index.y] = 0xFF0000;
			else if (data->map[real_pos.y][real_pos.x] == '0')
				data->mini_map[index.y][index.y] = 0xFFFFFF;
			real_pos.x++;
			index.x++;
		}
		index.y++;
		real_pos.y++;
	}
}
/* t_coord	get_offset(t_data *data, int size, t_coord index)
{
	t_coord	pos;

	if (index.x < size / 2)
		pos.x = data->m_pos.x - (size / 2);
	else if (index.x > size / 2)
		pos.x = data->m_pos.x + (size / 2);
	if (index.y < size / 2)
		pos.y = data->m_pos.y - (size / 2);
	else if (index.y > size / 2)
		pos.y = data->m_pos.y + (size / 2);
	return (pos);
} */
