/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/26 10:08:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*flag 0 -> operation in x coordinate
flag 1 -> operation in y coordinate
If the new position's x/y coordinate is in a square adjacent to a wall,
check if the distance from the new position is not lower than BUBBLE
(the minimum allowed distance the player can be to a wall).
This avoids cases where the move makes the player land at the edge of a wall,
which messes up the dda calculations.
*/
int	personal_space(t_data *data, double new, double pos, int flag)
{
	if ((!flag
			&& ((new > pos && data->map[data->m_pos.y][data->m_pos.x + 1] == '1'
				&& (double)(data->m_pos.x + 1) - new < BUBBLE)
		|| (new < pos && data->map[data->m_pos.y][data->m_pos.x - 1] == '1'
		&& new - (double)(data->m_pos.x) < BUBBLE)))
		|| (flag
		&& ((new > pos && data->map[data->m_pos.y + 1][data->m_pos.x] == '1'
		&& (double)(data->m_pos.y + 1) - new < BUBBLE)
		|| (new < pos && data->map[data->m_pos.y - 1][data->m_pos.x] == '1'
		&& new - (double)(data->m_pos.y) < BUBBLE))))
		return (1);
	return (0);
}

int	move(t_data *data, int flag, int dir)
{
	t_coord_d	new;

	if (dir)
	{
		new.x = (data->pos.x + data->direction.x * P_SPEED * flag);
		new.y = (data->pos.y + data->direction.y * P_SPEED * flag);
	}
	else
	{
		new.x = (data->pos.x + data->camera.x * P_SPEED * flag);
		new.y = (data->pos.y + data->camera.y * P_SPEED * flag);
	}
	if (data->map[(int)data->pos.y][(int)new.x] != '1'
		&& !personal_space(data, new.x, data->pos.x, 0))
	{
		data->pos.x = new.x;
		data->m_pos.x = data->pos.x;
	}
	if (data->map[(int)new.y][(int)data->pos.x] != '1'
		&& !personal_space(data, new.y, data->pos.y, 1))
	{
		data->pos.y = new.y;
		data->m_pos.y = data->pos.y;
	}
	return (0);
}

int	rotate(t_data *data, int flag)
{
	double	old_dir;
	double	old_cam;
	double	rot_speed;

	if (flag)
		rot_speed = ROTATION;
	else
		rot_speed = -ROTATION;
	old_dir = data->direction.x;
	data->direction.x = data->direction.x * cos(rot_speed) \
		- data->direction.y * sin(rot_speed);
	data->direction.y = old_dir * sin(rot_speed) \
		+ data->direction.y * cos(rot_speed);
	old_cam = data->camera.x;
	data->camera.x = data->camera.x * cos(rot_speed) \
		- data->camera.y * sin(rot_speed);
	data->camera.y = old_cam * sin(rot_speed) \
		+ data->camera.y * cos(rot_speed);
	return (0);
}
