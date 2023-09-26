/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:10:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/26 09:56:25 by gacorrei         ###   ########.fr       */
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
# include <limits.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 450
# define TEXTURE_W_H 64
# define FOV_FACTOR 0.66
# define P_SPEED 0.1
# define BUBBLE 0.1
# define ROTATION 0.04

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_coord_d
{
	double	x;
	double	y;
}	t_coord_d;

typedef struct s_img2
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img2;

/*For texture indexes: N = 0, S = 1, W = 2, E = 3*/
typedef struct s_data
{
	char		**map;
	int			map_x;
	int			map_y;
	t_coord		map_start;
	char		*nswe_paths[4];
	t_img2		nswe_images[4];
	int			floor;
	int			ceiling;
	int			count;
	void		*init;
	void		*window;
	t_img2		image;
	t_coord_d	direction;
	t_coord_d	camera;
	double		cam_x;
	t_coord_d	ray_dir;
	t_coord_d	pos;
	t_coord		m_pos;
	t_coord_d	side_dist;
	t_coord_d	d_dist;
	double		perp_wall_dist;
	t_coord		step;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_data;

/*main.c*/
int		print_error(char *message);
int		init_data(t_data *data);

/*map.c*/
int		check_forbidden(char *temp);
int		get_map_dimensions(t_data *data, int map_fd);
int		get_map(t_data *data, int map_fd);
int		map(t_data *data, char *map_path);

/*validate_elements.c*/
int		skip_spaces(char *str, int i);
int		elements_ok(t_data *data);
int		validate_elements(t_data *data, int map_fd);

/*texture_validation.c*/
int		validate_compass(t_data *data, char *temp, int i, int index);
int		test_colour(char *rgb);
int		get_colour(char *rgb);
int		validate_colour(t_data *data, char *temp, int i, int flag);
int		validate_texture(t_data *data, char *temp);

/*validate_map.c*/
char	*add_spaces(char *str, int len);
void	fill_edges(t_data *data);
void	update_start(t_data *data, int x, int y);
int		validate_map(t_data *data);

/*validate_map_edge.c*/
int		path(char c);
int		holes(t_data *data, int i, int j);
int		edge_check(t_data *data);

/*mlx.c*/
int		no_event(t_data *data);
int		key_release(int key, t_data *data);
int		close_window(t_data *data);
int		open_images(t_data *data);
int		mlx(t_data *data);

/*dda.c*/
void	set_coord(t_coord_d *coord, double x, double y);
void	get_start_dir(t_data *data);
void	step_dist(t_data *data);
void	pre_dda(t_data *data);
void	stepper(t_data *data, int flag);
void	dda(t_data *data);
void	post_dda(t_data *data);
void	calc_textures(t_data *data, int i);
void	put_pixel(t_img2 *img, int i, int j, int colour);
void	buffer_to_image(t_data *data, int i, int j);
void	draw_buffer(t_data *data);
int		big_loop(t_data *data);

/* movements.c */
int		move(t_data *data, int flag, int dir);
int		rotate(t_data *data, int flag);

/*clean.c*/
int		ft_free(void *ptr);
int		free_double(char **array);
void	free_window(t_data *data);
int		free_all(t_data *data);

#endif