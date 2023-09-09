#include "cub3d.h"

void	rot_angle(t_cub *cub, double angle)
{
	double	old_dir;
	double	old_plane;

	old_dir = cub->ray->dir.x;
	cub->ray->dir.x = cub->ray->dir.x * cos(-angle)
		- cub->ray->dir.y * sin(-angle);
	cub->ray->dir.y = old_dir * sin(-angle)
		+ cub->ray->dir.y * cos(-angle);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(-angle)
		- cub->ray->plane.y * sin(-angle);
	cub->ray->plane.y = old_plane * sin(-angle)
		+ cub->ray->plane.y * cos(-angle);
}

void	init_rot(t_cub *cub)
{
	int	x;
	int	y;

	x = cub->map->player.x;
	y = cub->map->player.y;
	if (cub->map->map[y][x] == 'N')
		rot_angle(cub, -PI / 2);
	else if (cub->map->map[y][x] == 'S')
		rot_angle(cub, PI / 2);
	else if (cub->map->map[y][x] == 'W')
		rot_angle(cub, PI);
}

