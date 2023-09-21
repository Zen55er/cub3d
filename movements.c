/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/21 14:51:05 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* int	move_vert(t_data *data, int flag)
{
	double	y;

	y = data->pos.y;
	if (flag)
	{
		y -= P_SPEED;
		if (!(data->map[(int)y][(int)data->pos.x] == '1'))
			data->pos.y = y;
		printf("y: %f\n", y);
	}
	else
	{
		y += P_SPEED;
		if (!(data->map[(int)y][(int)data->pos.x] == '1'))
			data->pos.y = y;
		printf("y: %f\n", y);
	}
	return (0);
} */
int	move_vert(t_data *data, int flag)
{
	t_coord	new;

	new.x = (int)(data->pos.x + data->direction.x * P_SPEED * flag);
	new.y = (int)(data->pos.y + data->direction.y * P_SPEED * flag);
	if (flag == 1)
		printf("moving forward\n");
	else
		printf("moving backward\n");
	if (new.x > 0 && new.x < data->map_x - 2 && data->map[(int)data->pos.y][new.x] != 1)
		data->pos.x += (double)(data->direction.x * P_SPEED * flag);
	if (new.y > 0 && new.y < data->map_y - 2 && data->map[new.y][(int)data->pos.x] != 1)
		data->pos.y += (double)(data->direction.y * P_SPEED * flag);
	data->m_pos.x = data->pos.x;
	data->m_pos.y = data->pos.y;
	return (0);
}

int	move_horz(t_data *data, int flag)
{
	t_coord	new;

	new.x = (int)(data->pos.x + data->camera.x * P_SPEED * flag);
	new.y = (int)(data->pos.y + data->camera.y * P_SPEED * flag);
	if (flag == 1)
		printf("moving right\n");
	else
		printf("moving left\n");
	if (new.x > 0 && new.x < data->map_x - 2 && data->map[(int)data->pos.y][new.x] != 1)
		data->pos.x += (double)(data->camera.x * P_SPEED * flag);
	if (new.y > 0 && new.y < data->map_y - 2 && data->map[new.y][(int)data->pos.x] != 1)
		data->pos.y += (double)(data->camera.y * P_SPEED * flag);
	data->m_pos.x = data->pos.x;
	data->m_pos.y = data->pos.y;
	return (0);
}

int	rotate(t_data *data, int flag)
{
	(void)data;
	if (flag == 1)
	{
		printf("turning right\n");
	}
	else
	{
		printf("turning left\n");
	}
	return (0);
}
