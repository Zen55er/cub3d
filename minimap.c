/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:50:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/22 16:21:23 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mini_map(t_data *data, int i, int j)
{
	int	colour;

	colour = 0x000000;
	put_pixel(&data->image, i, j, colour);
	return (0);
}