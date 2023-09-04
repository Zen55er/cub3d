/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:11:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/04 09:28:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*add_spaces(char *str, int len)
{
	char	*temp;
	int		i;

	temp = ft_strjoin_free(str, ft_strdup(" "));
	i = -1;
	while (++i < len - 1)
		temp = ft_strjoin_free(temp, ft_strdup(" "));
	return (temp);
}

void	fill_edges(t_data *data)
{
	int		i;
	int		len;

	i = -1;
	while (data->map[++i])
	{
		len = data->map_x - ft_strlen(data->map[i]);
		if (len)
			data->map[i] = add_spaces(data->map[i], len);
	}
	return ;
}

void	update_start(t_data *data, int x, int y)
{
	data->map_start.x = x;
	data->map_start.y = y;
	return ;
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	fill_edges(data);
	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (!start && (data->map[j][i] == 'N' || data->map[j][i] == 'S'
				|| data->map[j][i] == 'W' || data->map[j][i] == 'E') && ++start)
				update_start(data, i, j);
			else if (start && (data->map[j][i] == 'N' || data->map[j][i] == 'S'
				|| data->map[j][i] == 'W' || data->map[j][i] == 'E'))
				return (print_error("Found duplicate start position"));
		}
	}
	if (!data->map_start.x)
		return (print_error("Start position missing"));
	if (edge_check(data))
		return (1);
	return (0);
}
