/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:15:28 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:15:28 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include "mlx_int.h"

# define RGB_RED 0xFFA07A
# define RGB_BLACK 0x000000
# define RGB_GREEN 	0x7CFC00
# define RGB_SKY 0x7BCAEC
# define RGB_FLOOR 0x1957B5
# define DARK_BLUE 0x000066
# define GREY 0x606060

# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MKEYPRESS 1L

# define SPEED 0.08
# define ANGLE 0.05
# define PI 3.14159
# define OFFSET 0.25
# define VMOVE 0.0
# define UDIV 5
# define VDIV 5

# ifdef __linux__

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	A = 97,
	W = 119,
	S = 115,
	D = 100,
	RL = 65361,
	RR = 65363,
	SPC = 32,
	ESC = 65307
};
# else

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	A = 0,
	W = 13,
	S = 1,
	D = 2,
	RL = 123,
	RR = 124,
	ESC = 53
};
# endif

typedef struct s_vec2
{
	int			x;
	int			y;
	int			color;
}				t_vec2;

typedef struct s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct s_lst
{
	char			*tab;
	int				size;
	struct s_lst	*next;
}		t_lst;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	f;
	t_color	c;
	t_vec2	player;
	char	**map;
	t_vec2	map_size;
}			t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		i;
	int		bpp;
	int		linel;
	int		endian;
	t_vec2	win_size;
}	t_mlx;

typedef struct s_ray
{
	t_vec2	step;
	t_vec2	map;
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	ray_dir;
	t_vec2d	plane;
	t_vec2d	delta_dist;
	t_vec2d	side_dist;
	t_vec2d	ray_dir0;
	t_vec2d	ray_dir1;
	t_vec2d	floor;
	t_vec2d	floor_step;
	double	pos_z;
	double	row_dist;
	double	camera_x;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		hit;
	int		side;
}			t_ray;

typedef struct s_press
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		rl;
	int		rr;
}			t_press;

typedef struct s_cub
{
	t_press		*press;
	t_map		*map;
	t_mlx		mlx;
	t_mlx		north;
	t_mlx		south;
	t_mlx		west;
	t_mlx		east;
	t_ray		*ray;
}			t_cub;

/*----parsing----*/
t_map	*parse(char *path);
int		get_param(t_map **map, char *line);
int		check_player(t_map *map);
char	**check_map(char **map, t_vec2 *map_size);
int		is_line_for_map(char *line);
void	find_dir(t_map **map, char *line, int *res, int i);
int		put_dir(char **dir, char *line);

/*---lst_utils---*/
int		lst_add_back(t_lst **lst, char *tab);
int		free_lst(t_lst **lst);
int		lst_size(t_lst *lst);

/*----map_utils--*/
t_map	*init_map(void);
int		is_line_for_map(char *line);
int		free_tab(char **tab);
int		free_map(t_map *map);
int		check_isolation(char **tab, int size);
int		space_extension(char **map, int x);

int		empty_params(t_map *map);
int		empty_line(char *line);
char	*ignore_empty_lines(char *line, int fd);
int		put_color(t_color *color, char *line);
void	init_color(t_color *color);
int		get_color(t_ray **ray, t_cub *cub);
int		check_colors(char **rgb, t_color *color);

/*----display utils----*/
int		ft_key_choose(int key, t_cub *cub);
int		mouse_hook(t_cub *cub);
void	clear_screen(t_cub *cub);
void	ft_close(t_cub *cub);
void	pixel_put(t_mlx *data, int x, int y, int color);

int		draw_cub(t_cub *cub, t_ray *ray);
t_cub	*init_cub(t_map *map);
int		init_textures(t_cub **cub);

/*----key press utils----*/
int		init_press(t_cub **cub);
int		change_flag_0(int key, t_cub *cub);

/*----sprite utils----*/
void	texture_on_img(t_mlx *texture, t_cub **cub, t_vec2 tex, t_vec2 val);

/*----game loop----*/
int		update_game(t_cub *cub);

/*-----wall------*/
void	init_raydir(t_ray **ray, t_cub *cub, int x);
void	init_side_dist(t_ray **ray);
void	dda_algo(t_ray **ray, t_cub *cub);
int		get_color(t_ray **ray, t_cub *cub);
void	show_line(t_ray **ray, t_cub *cub, int x);

void	draw_back(t_cub *cub, t_ray **ray);
void	draw_side(t_mlx side, t_ray **ray, t_cub *cub, int x);
void	draw_stripe(t_ray **ray, t_cub *cub, int x);

/*----hooks----*/
void	init_rot(t_cub *cub);
int		check_move(double val, double start, double end);
void	forward(t_cub *cub);
void	back(t_cub *cub);
void	left(t_cub *cub);
void	right(t_cub *cub);
void	rot_left(t_cub *cub, double speed);
void	rot_right(t_cub *cub, double speed);
void	open_door(t_cub *cub);
int		verif_boundries(t_cub *cub, int x, int y);

/*------mlx------*/
void	close_mlx(t_cub *cub, t_mlx mlx);
#endif