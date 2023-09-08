#include "cub3d.h"

static void	close_mlx(t_cub *cub, t_mlx mlx)
{
	if (mlx.img)
		mlx_destroy_image(cub->mlx.mlx, mlx.img);
	if (mlx.win)
		mlx_destroy_window(cub->mlx.mlx, mlx.win);
	if (mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(mlx.mlx);
	}
}

void	ft_close(t_cub *cub)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (cub->map)
		free_map(cub->map);
	close_mlx(cub, cub->north);
	close_mlx(cub, cub->south);
	close_mlx(cub, cub->east);
	close_mlx(cub, cub->west);
	close_mlx(cub, cub->door);
	if (cub->press)
		free(cub->press);
	if (cub->ray)
	{
		free(cub->ray);
		cub->ray = NULL;
	}

	if (cub->sprite)
	{
		while (j < SPRITE_COUNT)
		{
			i = 0;
			while (i < cub->sprite[j].text_count)
			{
				close_mlx(cub, cub->sprite[j].text[i]);
				i++;
			}
			if (cub->sprite[j].text)
				free(cub->sprite[j].text);
			j++;
		}
		free(cub->sprite);
	}
	if (cub->z_buf)
		free(cub->z_buf);
	mlx_do_key_autorepeaton(cub->mlx.mlx);
	close_mlx(cub, cub->mlx);
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
	if (key == W || cub->press->w == 1)
	{
		// printf("cub->press : %d\n", cub->press->w);
		cub->press->w = 1;
		//forward(cub);
	}
	if (key == A || cub->press->a == 1)
	{
		cub->press->a = 1;
		//left(cub);
	}
	if (key == S || cub->press->s == 1)
	{
		cub->press->s = 1;
		back(cub);
	}
	if (key == D || cub->press->d == 1)
	{
		cub->press->d = 1;
		right(cub);
	}
	if (key == RL || cub->press->rl == 1)
	{
		cub->press->rl = 1;
		rot_left(cub);
	}
	if (key == RR || cub->press->rr == 1)
	{
		cub->press->rr = 1;
		rot_right(cub);
	}
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
