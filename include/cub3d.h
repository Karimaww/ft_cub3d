#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
// # include "../mlx/mlx.h"
# include <stdbool.h>
# include <stdio.h>
// # include "colors.h"
// # include "events.h"

// look up 
# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MKEYPRESS 1L

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	A = 33,
	W = 44,
	S = 55,
	D = 66
};

typedef struct s_vec2
{
	int			x;
	int			y;
}				t_vec2;

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
	int		bpp;
	int		linel;
	int		endian;
	t_vec2	win_size;
}	t_mlx;

typedef struct s_cub
{
	t_map	*map;
	t_mlx	*mlx;
	t_vec2	*pos;
}			t_cub;

/*----parsing----*/
t_map	*parse(char *path);
int		get_param(t_map **map, char *line);
int		check_player(t_map *map);

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
int		check_colors(char **rgb, t_color *color);

/*----display utils----*/
int	ft_key_choose(int key, t_cub *cub);
int	mouse_hook(t_cub *cub);

#endif