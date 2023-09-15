/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:03 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:03 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief These functions were taken from the previous project FdF and are
 * going to draw the lines of the triangle. They use the Bresenham algorithm.
 * @param d 
 * @return int 
 */
static int	set_i_d(int *d)
{
	if (*d < 0)
	{
		*d = -(*d);
		return (-1);
	}
	return (1);
}

void	line_low(t_cub *cub, t_vec2 v1, t_vec2 v2)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;
	yi = set_i_d(&dy);
	d = 2 * dy - dx;
	while (v1.x < v2.x)
	{
		pixel_put(&(cub->mlx), v1.x, v1.y, RGB_RED);
		if (d > 0)
		{
			v1.y += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		v1.x += 1;
	}
}

void	line_high(t_cub *cub, t_vec2 v1, t_vec2 v2)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;
	xi = set_i_d(&dx);
	d = 2 * dx - dy;
	while (v1.y < v2.y)
	{
		pixel_put(&(cub->mlx), v1.x, v1.y, RGB_RED);
		if (d > 0)
		{
			v1.x += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		v1.y += 1;
	}
}

void	draw_line(t_cub *cub, t_vec2 v1, t_vec2 v2)
{
	if (abs(v2.y - v1.y) < abs(v2.x - v1.x))
	{
		if (v1.x > v2.x)
			line_low(cub, v2, v1);
		else
			line_low(cub, v1, v2);
	}
	else
	{
		if (v1.y > v2.y)
			line_high(cub, v2, v1);
		else
			line_high(cub, v1, v2);
	}
}
