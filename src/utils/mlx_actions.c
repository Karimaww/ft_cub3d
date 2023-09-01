#include "cub3d.h"

void	ft_close(t_cub *cub)
{
	if (cub->map)
	{
		free_tab(cub->map->map);
		free(cub->map);
	}
	if (cub->mlx.img)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img);
	if (cub->mlx.win)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	if (cub->mlx.mlx)
	{
		//mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
	if (cub->ray)
		free(cub->ray);
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
			pixel_put(&(cub->mlx), j, i, 0);
			++j;
		}
		++i;
	}
}

int	ft_key_choose(int key, t_cub *cub)
{
	// printf("key : %d\n", key);
	if (key == ESC)
		ft_close(cub);
	if (key == W){
		//printf("hereeeeee pos x : %f\n", cub->ray->pos.x);
		hook_up(cub);
		printf("pos x : %f\n", cub->ray->pos->x);
	}
	if (key == A)
		hook_left(cub);
	if (key == S)
		hook_down(cub);
	if (key == D)
		hook_right(cub);
	clear_screen(cub);
	draw_cub(cub, cub->ray);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}

int	mouse_hook(t_cub *cub)
{
	ft_close(cub);
	return (0);
}
