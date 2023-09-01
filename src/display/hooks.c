#include "cub3d.h"

void	forward(t_cub *cub)
{
	if (cub->map->map[(int)(cub->ray->pos.x + cub->ray->dir.x * SPEED)]
		[(int)(cub->ray->pos.y)] != '1')
		cub->ray->pos.x += cub->ray->dir.x * SPEED;
	if (cub->map->map[(int)(cub->ray->pos.x)]
		[(int)(cub->ray->pos.y + cub->ray->dir.y * SPEED)] != '1')
		cub->ray->pos.y += cub->ray->dir.y * SPEED;
}

void	back(t_cub *cub)
{
	if (cub->map->map[(int)(cub->ray->pos.x - cub->ray->dir.x * SPEED)]
		[(int)(cub->ray->pos.y)] != '1')
		cub->ray->pos.x -= cub->ray->dir.x * SPEED;
	if (cub->map->map[(int)(cub->ray->pos.x)]
		[(int)(cub->ray->pos.y - cub->ray->dir.y * SPEED)] != '1')
		cub->ray->pos.y -= cub->ray->dir.y * SPEED;
}

void	left(t_cub *cub)
{
	if (cub->map->map[(int)(cub->ray->pos.x - cub->ray->plane.x * SPEED)]
		[(int)(cub->ray->pos.y)] != '1')
		cub->ray->pos.x -= cub->ray->plane.x * SPEED;
	if (cub->map->map[(int)(cub->ray->pos.x)]
		[(int)(cub->ray->pos.y - cub->ray->plane.y * SPEED)] != '1')
		cub->ray->pos.y -= cub->ray->plane.y * SPEED;
}

void	right(t_cub *cub)
{
	if (cub->map->map[(int)(cub->ray->pos.x + cub->ray->plane.x * SPEED)]
		[(int)(cub->ray->pos.y)] != '1')
		cub->ray->pos.x += cub->ray->plane.x * SPEED;
	if (cub->map->map[(int)(cub->ray->pos.x)]
		[(int)(cub->ray->pos.y + cub->ray->plane.y * SPEED)] != '1')
		cub->ray->pos.y += cub->ray->plane.y * SPEED;
}

void	rot_left(t_cub *cub)
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

void	rot_right(t_cub *cub)
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
