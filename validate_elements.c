/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:05:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/04 13:34:39 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	elements_ok(t_data *data)
{
	if (data->nswe_paths[0] && data->nswe_paths[1] && data->nswe_paths[2]
		&& data->nswe_paths[3] && data->floor >= 0 && data->ceiling >= 0)
		return (1);
	return (0);
}

int	validate_elements(t_data *data, int map_fd)
{
	char	*temp;

	while (1)
	{
		temp = gnl(map_fd);
		if (!temp)
			return (print_error("Missing texture elements"));
		data->count++;
		if (temp[0] != 0 && validate_texture(data, temp))
		{
			free(temp);
			return (1);
		}
		free(temp);
		if (elements_ok(data))
			break ;
	}
	return (0);
}
