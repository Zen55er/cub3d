/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:00:18 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/28 11:08:28 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	return ;
}

int	free_all(t_data *data)
{
	if (data->map)
	{
		free_double(data->map);
		free(data->map);
	}
	if (data->n_path)
		free(data->n_path);
	if (data->s_path)
		free(data->s_path);
	if (data->w_path)
		free(data->w_path);
	if (data->e_path)
		free(data->e_path);
	return (1);
}
