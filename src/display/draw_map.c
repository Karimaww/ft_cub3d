#include "cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->square_size)
	{
		j = 0;
		while (j < cub->square_size)
		{
			pixel_put(&(cub->mlx), x + i, y + j, color);
			j++;
		}
		i++;
	}
}
