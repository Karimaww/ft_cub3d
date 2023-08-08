#include "cub3d.h"

void	ft_close(t_cub *cub)
{
	if (cub->map)
	{
		free_map(cub->map->map, cub->map->sizey);
		free(cub->map);
	}
	if (cub->mlx.img)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img);
	if (cub->mlx.win)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
	if (cub)
		free(cub);
	exit(0);
}

void	clear_screen(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->mlx.win_size.y)
	{
		j = 0;
		while (j < cub->mlx.win_size.x)
		{
			pixel_put(&cub->mlx, j, i, 0);
			++j;
		}
		++i;
	}
}

int	ft_key_choose(int key, t_cub *cub)
{
	if (key == W || key == A || key == S || key == D)
		hook_move(cub, key);
	// if (key == ESC)
	// 	ft_close(cub);
	// if (key == SPACE)
	// 	get_orig_color(cub);
	// if (key == ARROW_UP || key == ARROW_DOWN)
	// 	hook_zoom(cub, key);
	// if (key == ARROW_LEFT || key == ARROW_RIGHT || key == R || key == T)
	// 	hook_rot(cub, key);
	// if (key == UP || key == DOWN)
	// 	hook_up_down(cub, key);
	// if (key == LEFT || key == RIGHT)
	// 	hook_left_right(cub, key);
	// if (key == HUP || key == HDOWN)
	// 	hook_height(cub, key);
	clear_screen(cub);
	draw_cub(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}

int	mouse_hook(t_cub *cub)
{
	ft_close(cub);
	return (0);
}