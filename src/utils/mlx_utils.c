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