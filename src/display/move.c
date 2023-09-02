#include "cub3d.h"

// void	forward(t_cub *cub)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = cub->ray->pos.x + cub->ray->dir.x * SPEED;
// 	new_y = cub->ray->pos.y + cub->ray->dir.y * SPEED;
// 	if (check_move(new_x, 0.0, cub->map->map_size.x)
// 		&& cub->map->map[(int)new_x][(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x = new_x;
// 	if (check_move(new_y, 0.0, cub->map->map_size.y)
// 		&& cub->map->map[(int)(cub->ray->pos.x)][(int)new_y] != '1')
// 		cub->ray->pos.y = new_y;
// }

// void	back(t_cub *cub)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = cub->ray->pos.x - cub->ray->dir.x * SPEED;
// 	new_y = cub->ray->pos.y - cub->ray->dir.y * SPEED;
// 	if (check_move(new_x, 0.0, cub->map->map_size.x)
// 		&& cub->map->map[(int)new_x][(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x = new_x;
// 	if (check_move(new_y, 0.0, cub->map->map_size.y)
// 		&& cub->map->map[(int)(cub->ray->pos.x)][(int)new_y] != '1')
// 		cub->ray->pos.y = new_y;
// }

// void	left(t_cub *cub)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = cub->ray->pos.x - cub->ray->plane.x * SPEED;
// 	new_y = cub->ray->pos.y - cub->ray->plane.y * SPEED;
// 	if (check_move(new_x, 0.0, cub->map->map_size.x)
// 		&& cub->map->map[(int)new_x][(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x = new_x;
// 	if (check_move(new_y, 0.0, cub->map->map_size.y)
// 		&& cub->map->map[(int)(cub->ray->pos.x)][(int)new_y] != '1')
// 		cub->ray->pos.y = new_y;
// }

// void	right(t_cub *cub)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = cub->ray->pos.x + cub->ray->plane.x * SPEED;
// 	new_y = cub->ray->pos.y + cub->ray->plane.y * SPEED;
// 	if (check_move(new_x, 0.0, cub->map->map_size.x)
// 		&& cub->map->map[(int)new_x][(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x = new_x;
// 	if (check_move(new_y, 0.0, cub->map->map_size.y)
// 		&& cub->map->map[(int)(cub->ray->pos.x)][(int)new_y] != '1')
// 		cub->ray->pos.y = new_y;
// }

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