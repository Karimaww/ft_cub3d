#include "cub3d.h"

int	draw_cub(t_cub *cub, t_ray *ray)
{
	int	x;

	x = 0;
	// Floor casting
	draw_back(cub, &ray);
	// Wall casting
	while (x < cub->mlx.win_size.x)
	{
		init_raydir(&ray, cub, x);
		//calculate step and initial sideDist
		init_side_dist(&ray);
		dda_algo(&ray, cub);
		show_line(&ray, cub, x);
		cub->sprite->z_buf[x] = ray->perp_dist;
		x++;
	}
	// Sprite casting
	draw_sprite(&cub, ray);
	return (EXIT_SUCCESS);
}
