/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:02:05 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/06 09:26:21 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Validates current element, if ok, keeps the path to the texture in memory*/
int	validate_compass(t_data *data, char *temp, int i, int index)
{
	i += 2;
	i = skip_spaces(temp, i);
	if (!temp[i])
		return (print_error("Invalid texture path"));
	if (data->nswe_paths[index])
		return (print_error("Duplicate texture"));
	if (ft_strcmp((temp + (ft_strlen(temp) - 4)), ".xpm"))
		return (print_error("Texture is not in .xpm format"));
	data->nswe_paths[index] = ft_substr(temp, i, ft_strlen(temp) - i);
	if (access(data->nswe_paths[index], R_OK))
		return (print_error("Invalid texture path"));
	return (0);
}

/*Tests RGB format*/
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
			&& free_double(test)))
		return (print_error("Wrong colour format"));
	while (test[++i])
	{
		j = -1;
		if ((ft_strlen(test[i]) > 3 || ft_atoi(test[i]) > 255)
			&& free_double(test))
			return (print_error("Wrong colour format"));
		while (test[i][++j])
			if (!ft_isdigit(test[i][j]) && free_double(test))
				return (print_error("Wrong colour format"));
	}
	free_double(test);
	return (0);
}

/*Returns converted colour*/
int	get_colour(char *rgb)
{
	int		r;
	int		g;
	int		b;
	char	**temp;

	temp = ft_split(rgb, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	free_double(temp);
	return ((r << 16) + (g << 8) + b);
}

/*Tests current colour line*/
int	validate_colour(t_data *data, char *temp, int i, int flag)
{
	i++;
	i = skip_spaces(temp, i);
	if ((!flag && data->floor != -1) || (flag && data->ceiling != -1))
		return (print_error("Duplicate colour"));
	if (!flag && !test_colour(&temp[i]))
		data->floor = get_colour(&temp[i]);
	else if (flag && !test_colour(&temp[i]))
		data->ceiling = get_colour(&temp[i]);
	if ((!flag && data->floor == -1) || (flag && data->ceiling == -1))
		return (1);
	return (0);
}

/*Tests current texture line*/
int	validate_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	if (strlen(temp) < 3)
		return (print_error("Misconfigured map file elements"));
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
