/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:10:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/28 09:58:19 by tlemos-m         ###   ########.fr       */
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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TEXTURE_W_H 360
# define FOV_FACTOR 0.66
# define P_SPEED 0.1
# define BUBBLE 0.1
# define ROTATION 0.05
# define MOUSE_LIM 25
# define MM_SIZE 9
# define PPT 30
# define M_MAP_P 0x17F9FF
# define M_MAP_W 0x005BC5
# define M_MAP_F 0x001449
# define M_MAP_V 0x012677

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

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}	t_keys;

/*For texture indexes: N = 0, S = 1, W = 2, E = 3*/
typedef struct s_data
{
	char		**map;
	int			map_x;
	int			map_y;
	t_coord		map_start;
	char		*nswe_paths[4];
	t_img2		nswe_images[4];
	t_keys		key_states;
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
	int			mini_map[MM_SIZE][MM_SIZE];
}				t_data;

/*main.c*/
int		print_error(char *message);
int		init_data(t_data *data);
void	init_data_2(t_data *data);

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
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		close_window(t_data *data);
int		open_images(t_data *data);
int		mlx(t_data *data);

/* mlx_utils.c */
int		init_image(t_data *data);
void	update_mouse_pos(int x, int y, t_data *data);
int		mouse_look(int x, int y, t_data *data);

/*dda.c*/
int		get_pixel(t_img2 img, int i, int j);
void	set_coord(t_coord_d *coord, double x, double y);
void	get_start_dir(t_data *data);
void	step_dist(t_data *data);
void	pre_dda(t_data *data);

/* dda_utils_1.c */
void	stepper(t_data *data, int flag);
void	dda(t_data *data);
void	post_dda(t_data *data);
int		choose_texture(t_data *data);
void	calc_textures(t_data *data, int i);

/* dda_utils_2.c */
void	set_colour(t_data *data, t_coord tex, t_coord_d pos_step, int i);
void	draw_ceiling_floor(t_data *data);
int		big_loop(t_data *data);

/* mini_map.c */
int		render_minimap(t_data *data);
int		draw_square(t_data *data, int i, int j, int c);
void	get_minimap(t_data *data);
void	put_color(t_data *data, t_coord spot, t_coord pos, t_coord temp);
void	reset_minimap(t_data *data);

/* movements.c */
int		move(t_data *data, int flag, t_coord_d dir_cam);
int		rotate(t_data *data, double rot_speed);
void	movement(t_data *data);

/*clean.c*/
int		ft_free(void *ptr);
int		free_double(char **array);
void	free_window(t_data *data);
int		free_all(t_data *data);

#endif