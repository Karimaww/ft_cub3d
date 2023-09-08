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