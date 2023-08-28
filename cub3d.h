/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:10:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/28 11:08:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <X11/keysym.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

typedef struct s_data
{
	char	**map;
	int		map_x;
	int		map_y;
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
}			t_data;

/*map.c*/
int		print_error(char *message);
int		skip_spaces(char *str, int i);
void	init_data(t_data *data);
int		copy_map(t_data *data, char *map_path);

/*clean.c*/
void	free_double(char **array);
int		free_all(t_data *data);

#endif