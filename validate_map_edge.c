/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_edge.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:13:35 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/20 13:58:13 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Returns 1 if entry is floor or player*/
int	path(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

/*Checks if edges have anything other than 1's*/
int	holes(t_data *data, int i, int j)
{
	int	k;
	int	l;
	int	m;
	int	n;

	k = i;
	while (k > 0 && data->map[j][++k] && path(data->map[j][k]))
		continue ;
	l = i;
	while (l > 0 && data->map[j][--l] && path(data->map[j][l]))
		continue ;
	m = j;
	while (m > 0 && m < data->map_y - 1
		&& data->map[++m][i] && path(data->map[m][i]))
		continue ;
	n = j;
	while (n > 0 && data->map[--n][i] && path(data->map[n][i]))
		continue ;
	if (!data->map[j][k] || data->map[j][k] == ' '
		|| !data->map[j][l] || data->map[j][l] == ' '
		|| (m == data->map_y - 1 && data->map[m][i] == '0')
		|| !data->map[m][i] || data->map[m][i] == ' '
		|| !data->map[n][i] || data->map[n][i] == ' ')
		return (1);
	return (0);
}

/*Iterates through map to check for holes in the walls
or incorrect player position*/
int	edge_check(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
			if (data->map[j][i] == '0')
				if (j == 0 || j == data->map_y - 1 || i == 0
					|| i == data->map_x - 1 || holes(data, i, j))
					return (print_error("Map is not surrounded by 1's"));
	}
	if (!data->map_start.x || data->map_start.x == data->map_x - 1
		|| !data->map_start.y || data->map_start.y == data->map_y - 1)
		return (print_error("Start position can't be on the edge of the map"));
	return (0);
}
