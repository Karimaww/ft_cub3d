#include "cub3d.h"

void	init_floor(t_ray **ray, t_cub *cub, int y)
{
	// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
	(*ray)->ray_dir0.x = (*ray)->dir.x - (*ray)->plane.x;
	(*ray)->ray_dir0.y = (*ray)->dir.y - (*ray)->plane.y;
	(*ray)->ray_dir1.x = (*ray)->dir.x + (*ray)->plane.x;
	(*ray)->ray_dir1.y = (*ray)->dir.y + (*ray)->plane.y;
	// Vertical position of the camera.
	(*ray)->pos_z = 0.5 * cub->mlx.win_size.y;
	// Horizontal distance from the camera to the floor for the current row.
    // 0.5 is the z position exactly in the middle between floor and ceiling.
	(*ray)->row_dist = (*ray)->pos_z
		/ (y - 0.5 * cub->mlx.win_size.y);  // Current y position compared to the center of the screen (the horizon)
	// calculate the real world step vector we have to add for each x (parallel to camera plane)
    // adding step by step avoids multiplications with a weight in the inner loop
	(*ray)->floor_step.x = (*ray)->row_dist
		* ((*ray)->ray_dir1.x - (*ray)->ray_dir0.x) / cub->mlx.win_size.x;
	(*ray)->floor_step.y = (*ray)->row_dist
		* ((*ray)->ray_dir1.y - (*ray)->ray_dir0.y) / cub->mlx.win_size.x;
	// real world coordinates of the leftmost column. This will be updated as we step to the right.
	(*ray)->floor.x = (*ray)->pos.x + (*ray)->row_dist * (*ray)->ray_dir0.x;
	(*ray)->floor.y = (*ray)->pos.y + (*ray)->row_dist * (*ray)->ray_dir0.y;
}

void	draw_floor_line(t_cub *cub, t_ray **ray, int y)
{
	int	x;

	x = 0;
	while (x < cub->mlx.win_size.x)
	{
		(*ray)->floor.x += (*ray)->floor_step.x;
		(*ray)->floor.y += (*ray)->floor_step.y;
		int color;
		// Floor
		color = RGB_FLOOR;
		// if ((*ray)->side == 1)
		// 	color = (color >> 1) & 8355711;
		pixel_put(&(cub->mlx), x, y, color);
		// Ceiling
		color = RGB_SKY;
		// if ((*ray)->side == 1)
		// 	color = (color >> 1) & 8355711;
		pixel_put(&(cub->mlx), x, cub->mlx.win_size.y - y - 1, color);
		x++;
	}
}

void	draw_back(t_cub *cub, t_ray **ray)
{
	int	y;

	y = 0;
	// Floor casting
	while (y < cub->mlx.win_size.y)
	{
		init_floor(ray, cub, y);
		draw_floor_line(cub, ray, y);
		y++;
	}
}
