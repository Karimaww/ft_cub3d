#include "cub3d.h"

// void	forward(t_cub *cub)
// {
// 	if (cub->map->map[(int)(cub->ray->pos.x + cub->ray->dir.x * SPEED)]
// 		[(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x += cub->ray->dir.x * SPEED;
// 	if (cub->map->map[(int)(cub->ray->pos.x)]
// 		[(int)(cub->ray->pos.y + cub->ray->dir.y * SPEED)] != '1')
// 		cub->ray->pos.y += cub->ray->dir.y * SPEED;
// }
void forward(t_cub *cub)
{
    double new_x = cub->ray->pos.x + cub->ray->dir.x * SPEED;
    double new_y = cub->ray->pos.y + cub->ray->dir.y * SPEED;

    if (cub->map->map[(int)new_x][(int)cub->ray->pos.y] != '1' &&
        cub->map->map[(int)cub->ray->pos.x][(int)new_y] != '1')
    {
        cub->ray->pos.x = new_x;
        cub->ray->pos.y = new_y;
    }
}

// void	back(t_cub *cub)
// {
// 	if (cub->map->map[(int)(cub->ray->pos.x - cub->ray->dir.x * SPEED)]
// 		[(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x -= cub->ray->dir.x * SPEED;
// 	if (cub->map->map[(int)(cub->ray->pos.x)]
// 		[(int)(cub->ray->pos.y - cub->ray->dir.y * SPEED)] != '1')
// 		cub->ray->pos.y -= cub->ray->dir.y * SPEED;
// }
void back(t_cub *cub)
{
    double new_x = cub->ray->pos.x - cub->ray->dir.x * SPEED;
    double new_y = cub->ray->pos.y - cub->ray->dir.y * SPEED;

    if (cub->map->map[(int)new_x][(int)cub->ray->pos.y] != '1' &&
        cub->map->map[(int)cub->ray->pos.x][(int)new_y] != '1')
    {
        cub->ray->pos.x = new_x;
        cub->ray->pos.y = new_y;
    }
}


// void	left(t_cub *cub)
// {
// 	if (cub->map->map[(int)(cub->ray->pos.x - cub->ray->plane.x * SPEED)]
// 		[(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x -= cub->ray->plane.x * SPEED;
// 	if (cub->map->map[(int)(cub->ray->pos.x)]
// 		[(int)(cub->ray->pos.y - cub->ray->plane.y * SPEED)] != '1')
// 		cub->ray->pos.y -= cub->ray->plane.y * SPEED;
// }
void left(t_cub *cub)
{
    double new_x = cub->ray->pos.x - cub->ray->plane.x * SPEED;
    double new_y = cub->ray->pos.y - cub->ray->plane.y * SPEED;

    if (cub->map->map[(int)new_x][(int)cub->ray->pos.y] != '1' &&
        cub->map->map[(int)cub->ray->pos.x][(int)new_y] != '1')
    {
        cub->ray->pos.x = new_x;
        cub->ray->pos.y = new_y;
    }
}


// void	right(t_cub *cub)
// {
// 	if (cub->map->map[(int)(cub->ray->pos.x + cub->ray->plane.x * SPEED)]
// 		[(int)(cub->ray->pos.y)] != '1')
// 		cub->ray->pos.x += cub->ray->plane.x * SPEED;
// 	if (cub->map->map[(int)(cub->ray->pos.x)]
// 		[(int)(cub->ray->pos.y + cub->ray->plane.y * SPEED)] != '1')
// 		cub->ray->pos.y += cub->ray->plane.y * SPEED;
// }
void right(t_cub *cub)
{
    double new_x = cub->ray->pos.x + cub->ray->plane.x * SPEED;
    double new_y = cub->ray->pos.y + cub->ray->plane.y * SPEED;

    if (cub->map->map[(int)new_x][(int)cub->ray->pos.y] != '1' &&
        cub->map->map[(int)cub->ray->pos.x][(int)new_y] != '1')
    {
        cub->ray->pos.x = new_x;
        cub->ray->pos.y = new_y;
    }
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
	cub->ray->dir.y = old_dir * sin(-ANGLE) + cub->ray->dir.y * cos(-ANGLE);
	old_plane = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(-ANGLE)
		- cub->ray->plane.y * sin(-ANGLE);
	cub->ray->plane.y = old_plane * sin(-ANGLE) + cub->ray->plane.y * cos(-ANGLE);
}
