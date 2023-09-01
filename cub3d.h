/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:10:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/01 09:35:29 by gacorrei         ###   ########.fr       */
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

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/*For texture indexes: N = 0, S = 1, W = 2, E = 3*/
typedef struct s_data
{
	char		**map;
	int			map_x;
	int			map_y;
	t_coord		map_start;
	char		*nswe_paths[4];
	int			floor;
	int			ceiling;
	int			count;
}			t_data;

/*map.c*/
int		print_error(char *message);
int		skip_spaces(char *str, int i);
int		elements_ok(t_data *data);
int		validate_elements(t_data *data, int map_fd);
int		forbidden(char c);
int		check_forbidden(char *temp);
int		get_map_dimensions(t_data *data, int map_fd);
int		map(t_data *data, char *map_path);
void	init_data(t_data *data);

/*texture_validation.c*/
int		validate_compass(t_data *data, char *temp, int i, int index);
int		test_colour(char *rgb);
int		get_colour(char *rgb);
int		validate_colour(t_data *data, char *temp, int i, int flag);
int		validate_texture(t_data *data, char *temp);

/*clean.c*/
int		ft_free(void *ptr);
int		free_double(char ***array);
int		free_all(t_data *data);

#endif