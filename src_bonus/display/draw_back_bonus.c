/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:56 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:16:56 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief ray->dir for leftmost ray (x = 0) and rightmost ray (x = w)
 * pos_z : vertical position of the camera
 * row_dist : horizontal distance from the camera to the floor for the current
 * row 0.5 is the z position exactly in the middle between floor and ceiling.
 * row_dist : current y position compared to the center of the screen
 * (the horizon) calculate the real world step vector we have to add for each x
 * (parallel to camera plane) adding step by step avoids multiplications with a
 * weight in the inner loop
 * floor : real world coordinates of the leftmost column. This will be updated
 * as we step to the right.
 * @param ray 
 * @param cub 
 * @param y 
 */
void	init_floor(t_ray **ray, t_cub *cub, int y)
{
	(*ray)->ray_dir0.x = (*ray)->dir.x - (*ray)->plane.x;
	(*ray)->ray_dir0.y = (*ray)->dir.y - (*ray)->plane.y;
	(*ray)->ray_dir1.x = (*ray)->dir.x + (*ray)->plane.x;
	(*ray)->ray_dir1.y = (*ray)->dir.y + (*ray)->plane.y;
	(*ray)->pos_z = 0.5 * cub->mlx.win_size.y;
	(*ray)->row_dist = (*ray)->pos_z / (y - 0.5 * cub->mlx.win_size.y);
	(*ray)->floor_step.x = (*ray)->row_dist
		* ((*ray)->ray_dir1.x - (*ray)->ray_dir0.x) / cub->mlx.win_size.x;
	(*ray)->floor_step.y = (*ray)->row_dist
		* ((*ray)->ray_dir1.y - (*ray)->ray_dir0.y) / cub->mlx.win_size.x;
	(*ray)->floor.x = (*ray)->pos.x + (*ray)->row_dist * (*ray)->ray_dir0.x;
	(*ray)->floor.y = (*ray)->pos.y + (*ray)->row_dist * (*ray)->ray_dir0.y;
}

static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	draw_floor_line(t_cub *cub, t_ray **ray, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < cub->mlx.win_size.x)
	{
		(*ray)->floor.x += (*ray)->floor_step.x;
		(*ray)->floor.y += (*ray)->floor_step.y;
		color = create_rgb(cub->map->f.r, cub->map->f.g, cub->map->f.b);
		pixel_put(&(cub->mlx), x, y, color);
		color = create_rgb(cub->map->c.r, cub->map->c.g, cub->map->c.b);
		pixel_put(&(cub->mlx), x, cub->mlx.win_size.y - y - 1, color);
		x++;
	}
}

void	draw_back(t_cub *cub, t_ray **ray)
{
	int	y;

	y = 0;
	while (y < cub->mlx.win_size.y)
	{
		init_floor(ray, cub, y);
		draw_floor_line(cub, ray, y);
		y++;
	}
}
