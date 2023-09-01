#include "cub3d.h"

void	hook_up(t_cub *cub)
{
	if (cub->map->map[(int)(cub->ray->pos->x + cub->ray->dir.x * 0.25)]
		[(int)(cub->ray->pos->y)] == '0')
	{
		cub->ray->pos->x += cub->ray->dir.x * 0.25;
	}
	if (cub->map->map[(int)(cub->ray->pos->x)]
		[(int)(cub->ray->pos->y + cub->ray->dir.y * 0.25)] == '0')
	{
		cub->ray->pos->y += cub->ray->dir.y * 0.25;
	}
}

void	hook_down(t_cub *cub)
{
	if (cub->map->map[(int)(cub->ray->pos->x - cub->ray->dir.x * 0.25)]
		[(int)(cub->ray->pos->y)] == '0')
		cub->ray->pos->x -= cub->ray->dir.x * 0.25;
	if (cub->map->map[(int)(cub->ray->pos->x)]
		[(int)(cub->ray->pos->y - cub->ray->dir.y * 0.25)] == '0')
		cub->ray->pos->y -= cub->ray->dir.y * 0.25;
}

void	hook_left(t_cub *cub)
{
	double	old_dir;
	double	old_plane;

	old_dir = cub->ray->dir.x;
	cub->ray->dir.x = cub->ray->dir.x * cos(0.08)
		- cub->ray->dir.y * sin(0.08);
	cub->ray->dir.y = old_dir * sin(0.08) + cub->ray->dir.y * cos(0.08);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(0.08)
		- cub->ray->plane.y * sin(0.08);
	cub->ray->plane.y = old_plane * sin(0.08) + cub->ray->plane.y * cos(0.08);
}

void	hook_right(t_cub *cub)
{
	double	old_dir;
	double	old_plane;

	old_dir = cub->ray->dir.x;
	cub->ray->dir.x = cub->ray->dir.x * cos(-0.08)
		- cub->ray->dir.y * sin(-0.08);
	cub->ray->dir.y = old_dir * sin(-0.08) + cub->ray->dir.y * cos(-0.08);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(-0.08)
		- cub->ray->plane.y * sin(-0.08);
	cub->ray->plane.y = old_plane * sin(-0.08) + cub->ray->plane.y * cos(-0.08);
}
