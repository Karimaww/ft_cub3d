#include "cub3d.h"

int	check_move(double val, double start, double end)
{
	return (val >= start && val < end);
}

void	rot_left(t_cub *cub)
{
	double	old_dir;
	double	old_plane;

	old_dir = cub->ray->dir.x;
	cub->ray->dir.x = cub->ray->dir.x * cos(ANGLE)
		- cub->ray->dir.y * sin(ANGLE);
	cub->ray->dir.y = old_dir * sin(ANGLE) + cub->ray->dir.y * cos(ANGLE);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(ANGLE)
		- cub->ray->plane.y * sin(ANGLE);
	cub->ray->plane.y = old_plane * sin(ANGLE) + cub->ray->plane.y * cos(ANGLE);
}

void	rot_right(t_cub *cub)
{
	double	old_dir;
	double	old_plane;

	old_dir = cub->ray->dir.x;
	cub->ray->dir.x = cub->ray->dir.x * cos(-ANGLE)
		- cub->ray->dir.y * sin(-ANGLE);
	cub->ray->dir.y = old_dir * sin(-ANGLE)
		+ cub->ray->dir.y * cos(-ANGLE);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(-ANGLE)
		- cub->ray->plane.y * sin(-ANGLE);
	cub->ray->plane.y = old_plane * sin(-ANGLE)
		+ cub->ray->plane.y * cos(-ANGLE);
}
