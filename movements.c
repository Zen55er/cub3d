/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/27 14:46:57 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*flag 0 -> operation in x coordinate
flag 1 -> operation in y coordinate
If the new position's x/y coordinate is in a square adjacent to a wall,
check if the distance from the new position is not lower than BUBBLE
(the minimum allowed distance the player can be to a wall).
This avoids cases where the move makes the player land at the edge of a wall,
which messes up the dda calculations.*/
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

int	move(t_data *data, int flag, t_coord_d dir_cam)
{
	t_coord_d	new;

	new.x = (data->pos.x + dir_cam.x * P_SPEED * flag);
	new.y = (data->pos.y + dir_cam.y * P_SPEED * flag);
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

int	rotate(t_data *data, double rot_speed)
{
	double	old_dir;
	double	old_cam;

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

void	movement(t_data *data)
{
	if (data->key_states.w)
		move(data, 1, data->direction);
	if (data->key_states.s)
		move(data, -1, data->direction);
	if (data->key_states.a)
		move(data, -1, data->camera);
	if (data->key_states.d)
		move(data, 1, data->camera);
	if (data->key_states.l)
		rotate(data, -ROTATION);
	if (data->key_states.r)
		rotate(data, ROTATION);
	return ;
}
