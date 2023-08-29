/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:00:18 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/29 11:18:29 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_double(char ***array)
{
	int	i;

	i = -1;
	while (*array[++i])
		free(*array[i]);
	free(*array);
	return (1);
}

int	free_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->map)
		free_double(&data->map);
	while (++i < 4)
		if (data->nswe_paths[i])
			free(data->nswe_paths[i]);
	return (1);
}
