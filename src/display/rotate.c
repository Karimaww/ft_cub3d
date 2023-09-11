#include "cub3d.h"

int	check_move(double val, double start, double end)
{
	return (val >= start && val < end);
}

void	rot_left(t_cub *cub, double speed)
{
	double	old_dir;
	double	old_plane;
	double	angle;

	old_dir = cub->ray->dir.x;
	angle = ANGLE * speed;
	cub->ray->dir.x = cub->ray->dir.x * cos(angle)
		- cub->ray->dir.y * sin(angle);
	cub->ray->dir.y = old_dir * sin(angle) + cub->ray->dir.y * cos(angle);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(angle)
		- cub->ray->plane.y * sin(angle);
	cub->ray->plane.y = old_plane * sin(angle) + cub->ray->plane.y * cos(angle);
}

void	rot_right(t_cub *cub, double speed)
{
	double	old_dir;
	double	old_plane;
	double	angle;

	old_dir = cub->ray->dir.x;
	angle = ANGLE * speed;
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
