/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:00:18 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/26 12:08:29 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Frees memory and returns 1.
Used to shorten functions*/
int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

/*Receives address of 2d array to free everything*/
int	free_double(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = 0;
	return (1);
}

/*Frees created display and mlx_init*/
/* void	free_window(t_data *data)
{
	free(data->init);
	return ;
} */

/*Checks each allocated variable and calls necessary function to free it*/
int	free_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->map)
		free_double(data->map);
	while (++i < 4)
	{
		if (data->nswe_paths[i])
			free(data->nswe_paths[i]);
		if (data->nswe_images[i].mlx_img)
			mlx_destroy_image(data->init, data->nswe_images[i].mlx_img);
	}
	if (data->window)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	return (1);
}
