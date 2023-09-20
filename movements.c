/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/20 14:58:42 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int move_vert(t_data *data, int flag)
{
    double  y;
     
    y = data->pos.y;
    if (flag)
    {
        y -= P_SPEED;
        if (!(data->map[(int)y][(int)data->pos.x] == '1'))
            data->pos.y = y;
        printf("y: %f\n", y);
    }
    else
    {
        y += P_SPEED;
        if (!(data->map[(int)y][(int)data->pos.x] == '1'))
            data->pos.y = y;
        printf("y: %f\n", y);
    }
    return (0);
}

int move_horz(t_data *data, int flag)
{
    double  x;

    x = data->pos.x;
    if (flag)
    {
        x += P_SPEED;
        if (!(data->map[(int)(data->pos.y)][(int)x] == '1'))
            data->pos.x = x;
        printf("x: %f\n", x);
    }
    else
    {
        x -= P_SPEED;
        if (!(data->map[(int)(data->pos.y)][(int)x] == '1'))
            data->pos.x = x;
        printf("x: %f\n", x);
    }
    return (0);
}

int rotate(t_data *data, int flag)
{
    (void)data;
    if (flag)
    {
        printf("RIGHT\n");
    }
    else
    {
        printf("LEFT\n");
    }
    return (0);
}
