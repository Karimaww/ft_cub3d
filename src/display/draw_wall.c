#include "cub3d.h"

void	init_raydir(t_ray **ray, t_cub *cub, int x)
{
	//calculate ray position and direction
	(*ray)->camera_x = 2 * x / (double)(cub->mlx.win_size.x) - 1; //x-coordinate in camera space
	(*ray)->ray_dir.x = (*ray)->dir.x + (*ray)->plane.x * (*ray)->camera_x;
	(*ray)->ray_dir.y = (*ray)->dir.y + (*ray)->plane.y * (*ray)->camera_x;
	//which box of the map we're in
	(*ray)->map.x = (int)((*ray)->pos.x);
	(*ray)->map.y = (int)((*ray)->pos.y);

	//length of ray from one x or y-side to next x or y-side
	if ((*ray)->ray_dir.x == 0)
		(*ray)->delta_dist.x = 1e30;
	if ((*ray)->ray_dir.y == 0)
		(*ray)->delta_dist.y = 1e30;
	(*ray)->delta_dist.x = fabs(1 / (*ray)->ray_dir.x);
	(*ray)->delta_dist.y = fabs(1 / (*ray)->ray_dir.y);
}

void	init_side_dist(t_ray **ray)
{
	//length of ray from current position to next x or y-side
	//what direction to step in x or y-direction (either +1 or -1)
	if ((*ray)->ray_dir.x < 0)
	{
		(*ray)->step.x = -1;
		(*ray)->side_dist.x = ((*ray)->pos.x - (*ray)->map.x)
			* (*ray)->delta_dist.x;
	}
	else
	{
		(*ray)->step.x = 1;
		(*ray)->side_dist.x = ((*ray)->map.x + 1.0 - (*ray)->pos.x)
			* (*ray)->delta_dist.x;
	}
	if ((*ray)->ray_dir.y < 0)
	{
		(*ray)->step.y = -1;
		(*ray)->side_dist.y = ((*ray)->pos.y - (*ray)->map.y)
			* (*ray)->delta_dist.y;
	}
	else
	{
		(*ray)->step.y = 1;
		(*ray)->side_dist.y = ((*ray)->map.y + 1.0 - (*ray)->pos.y)
			* (*ray)->delta_dist.y;
	}
}

void	dda_algo(t_ray **ray, t_cub *cub)
{
	//was there a wall hit?
	(*ray)->hit = 0;
	//perform DDA
	while ((*ray)->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if ((*ray)->side_dist.x < (*ray)->side_dist.y)
		{
			(*ray)->side_dist.x += (*ray)->delta_dist.x;
			(*ray)->map.x += (*ray)->step.x;
			(*ray)->side = 0;
		}
		else
		{
			(*ray)->side_dist.y += (*ray)->delta_dist.y;
			(*ray)->map.y += (*ray)->step.y;
			(*ray)->side = 1;
		}
		//Check if ray has hit a wall
		if (cub->map->map[(*ray)->map.x][(*ray)->map.y] == '1')
			(*ray)->hit = 1;
	}
}

int	get_color(t_ray **ray, t_cub *cub)
{
	int		color;

	if (cub->map->map[(*ray)->map.x][(*ray)->map.y] == '0')
		color = RGB_BLACK;
	if (cub->map->map[(*ray)->map.x][(*ray)->map.y] == '1')
		color = RGB_RED;
	if (cub->map->map[(*ray)->map.x][(*ray)->map.y] == ' ')
		color = RGB_GREEN;
	//give x and y sides different brightness
	if ((*ray)->side == 1)
		color = color / 2;
	return (color);
}

void	show_line(t_ray **ray, t_cub *cub, int x)
{
	double	perp_dist;
	int		line_h;

	//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	if ((*ray)->side == 0)
		perp_dist = ((*ray)->side_dist.x - (*ray)->delta_dist.x);
	else
		perp_dist = ((*ray)->side_dist.y - (*ray)->delta_dist.y);
	//Calculate height of line to draw on screen
	line_h = (int)(cub->mlx.win_size.y / perp_dist);
	//calculate lowest and highest pixel to fill in current stripe
	(*ray)->draw_start = -line_h / 2 + cub->mlx.win_size.y / 2;
	if ((*ray)->draw_start < 0)
		(*ray)->draw_start = 0;
	(*ray)->draw_end = line_h / 2 + cub->mlx.win_size.y / 2;
	if ((*ray)->draw_end >= cub->mlx.win_size.y)
		(*ray)->draw_end = cub->mlx.win_size.y - 1;
	draw_stripe(ray, cub, x);
}
