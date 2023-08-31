/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:02:05 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/31 15:31:27 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_compass(t_data *data, char *temp, int i, int index)
{
	i += 2;
	i = skip_spaces(temp, i);
	if (data->nswe_paths[index])
		return (print_error("Duplicate texture"));
	data->nswe_paths[index] = ft_substr(temp, i, ft_strlen(temp) - i);
	if (access(data->nswe_paths[index], R_OK))
		return (print_error("Invalid texture path"));
	return (0);
}

int	test_colour(char *rgb)
{
	int		i;
	int		j;
	char	**test;

	i = -1;
	if (!rgb)
		return (print_error("Wrong colour format"));
	test = ft_split(rgb, ',');
	if (!test || ((!test[0] || !test[1] || !test[2] || test[3])
			&& free_double(&test)))
		return (print_error("Wrong colour format"));
	while (test[++i])
	{
		j = -1;
		if ((ft_strlen(test[i]) > 3 || ft_atoi(test[i]) > 255)
			&& free_double(&test))
			return (print_error("Wrong colour format"));
		while (test[i][++j])
			if (!ft_isdigit(test[i][j]) && free_double(&test))
				return (print_error("Wrong colour format"));
	}
	return (0);
}

int	get_colour(char *rgb)
{
	int		i;
	int		r;
	int		g;
	int		b;
	char	**temp;

	i = -1;
	temp = ft_split(rgb, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	free_double(&temp);
	return ((r << 16) + (g << 8) + b);
}

int	validate_colour(t_data *data, char *temp, int i, int flag)
{
	i++;
	i = skip_spaces(temp, i);
	if ((!flag && data->floor) || (flag && data->ceiling))
		return (print_error("Duplicate colour"));
	if (!flag && !test_colour(&temp[i]))
		data->floor = get_colour(&temp[i]);
	else if (flag && !test_colour(&temp[i]))
		data->ceiling = get_colour(&temp[i]);
	return (0);
}

int	validate_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	i = skip_spaces(temp, i);
	if (temp[i] == 'N' && temp[i + 1] == 'O' && ft_isspace(temp[i + 2]))
		return (validate_compass(data, temp, i, 0));
	else if (temp[i] == 'S' && temp[i + 1] == 'O' && ft_isspace(temp[i + 2]))
		return (validate_compass(data, temp, i, 1));
	else if (temp[i] == 'W' && temp[i + 1] == 'E' && ft_isspace(temp[i + 2]))
		return (validate_compass(data, temp, i, 2));
	else if (temp[i] == 'E' && temp[i + 1] == 'A' && ft_isspace(temp[i + 2]))
		return (validate_compass(data, temp, i, 3));
	else if (temp[i] == 'F' && ft_isspace(temp[i + 1]))
		return (validate_colour(data, temp, i, 0));
	else if (temp[i] == 'C' && ft_isspace(temp[i + 1]))
		return (validate_colour(data, temp, i, 1));
	return (print_error("Misconfigured map file elements"));
}
