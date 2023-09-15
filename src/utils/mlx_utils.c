#include "cub3d.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->win_size.x || y >= data->win_size.y
		|| x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	close_mlx(t_cub *cub, t_mlx mlx)
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
