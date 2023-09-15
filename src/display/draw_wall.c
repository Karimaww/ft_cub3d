/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:14 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:16:14 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief ray_dir : calculate ray position and direction
 * camera_x : x-coordinate in camera space
 * map : which box of the map we're in
 * delta_dist : length of ray from one x or y-side to next x or y-side
 * @param ray 
 * @param cub 
 * @param x 
 */
void	init_raydir(t_ray **ray, t_cub *cub, int x)
{
	(*ray)->camera_x = (2 * x / (double)(cub->mlx.win_size.x) - 1) * -1;
	(*ray)->ray_dir.x = (*ray)->dir.x + (*ray)->plane.x * (*ray)->camera_x;
	(*ray)->ray_dir.y = (*ray)->dir.y + (*ray)->plane.y * (*ray)->camera_x;
	(*ray)->map.x = (int)((*ray)->pos.x);
	(*ray)->map.y = (int)((*ray)->pos.y);
	if ((*ray)->ray_dir.x == 0)
		(*ray)->delta_dist.x = 1e30;
	if ((*ray)->ray_dir.y == 0)
		(*ray)->delta_dist.y = 1e30;
	(*ray)->delta_dist.x = fabs(1 / (*ray)->ray_dir.x);
	(*ray)->delta_dist.y = fabs(1 / (*ray)->ray_dir.y);
}

/**
 * @brief Checks the length of ray from current position to next x or y-side
 * Determines what direction to step in x or y-direction (either +1 or -1)
 * @param cub
 * @return void
 */
void	init_side_dist(t_ray **ray)
{
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

/**
 * @brief Performs the dda algorithm which checks if a wall was hit and
 * advances until it is.
 * @param cub
 * @return void
 */
void	dda_algo(t_ray **ray, t_cub *cub)
{
	(*ray)->hit = 0;
	while ((*ray)->hit == 0)
	{
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
		if (cub->map->map[(*ray)->map.y][(*ray)->map.x] == '1')
			(*ray)->hit = 1;
	}
}

int	get_color(t_ray **ray, t_cub *cub)
{
	int		color;

	if (cub->map->map[(*ray)->map.y][(*ray)->map.x] == '0')
		color = RGB_BLACK;
	if (cub->map->map[(*ray)->map.y][(*ray)->map.x] == '1')
		color = RGB_RED;
	if (cub->map->map[(*ray)->map.y][(*ray)->map.x] == ' ')
		color = RGB_GREEN;
	if ((*ray)->side == 1)
		color = color / 2;
	return (color);
}

/**
 * @brief side : calculate distance projected on camera direction
 * (Euclidean distance would give fisheye effect!)
 * line_h : calculate height of line to draw on screen
 * draw_start : calculate lowest and highest pixel to fill in current stripe
 * @param ray 
 * @param cub 
 * @param x 
 */
void	show_line(t_ray **ray, t_cub *cub, int x)
{
	if ((*ray)->side == 0)
		(*ray)->perp_dist = ((*ray)->side_dist.x - (*ray)->delta_dist.x);
	else
		(*ray)->perp_dist = ((*ray)->side_dist.y - (*ray)->delta_dist.y);
	(*ray)->line_h = (int)(cub->mlx.win_size.y / (*ray)->perp_dist);
	(*ray)->draw_start = -(*ray)->line_h / 2 + cub->mlx.win_size.y / 2;
	if ((*ray)->draw_start < 0)
		(*ray)->draw_start = 0;
	(*ray)->draw_end = (*ray)->line_h / 2 + cub->mlx.win_size.y / 2;
	if ((*ray)->draw_end >= cub->mlx.win_size.y)
		(*ray)->draw_end = cub->mlx.win_size.y - 1;
	draw_stripe(ray, cub, x);
}
