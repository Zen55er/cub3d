/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:50:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/25 14:37:10 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mini_map(t_data *data, int i, int j)
{
	int		colour;
	t_coord	pixel;
	t_coord	index;
	
	pixel.x = (i * data->map_x) / WINDOW_WIDTH;
	pixel.y = (j * data->map_y) / WINDOW_HEIGHT;
	// printf("m_pos.x: %i\tm_pos.y: %i\n", data->m_pos.x, data->m_pos.y);
	if (data->m_pos.x == pixel.x && data->m_pos.y == pixel.y)
		colour = 0x00FF00;
	else if (data->map[pixel.y][pixel.x] == '0')
		colour = 0xFFFFFF;
	else
		colour = 0x000000;
	index.y = -1;
	while (++index.y < 4)
		put_pixel(&data->image, i, (j + index.y), colour);;
	return (j + index.y);
}