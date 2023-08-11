#include "cub3d.h"

static int	set_i_d(int *d)
{
	if (*d < 0)
	{
		*d = -(*d);
		return (-1);
	}
	return (1);
}

void	line_low(t_cub *cub, t_vec2 p1, t_vec2 p2, float dist)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	yi = set_i_d(&dy);
	d = 2 * dy - dx;
	while (p1.x < p2.x)
	{
		pixel_put(&(cub->mlx), p1.x, p1.y,
			get_color(p1, p2, dist));
		if (d > 0)
		{
			p1.y += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		p1.x += 1;
	}
}

void	line_high(t_cub *cub, t_vec2 p1, t_vec2 p2, float dist)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	xi = set_i_d(&dx);
	d = 2 * dx - dy;
	while (p1.y < p2.y)
	{
		pixel_put(&(cub->mlx), p1.x, p1.y,
			get_color(p1, p2, dist));
		if (d > 0)
		{
			p1.x += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		p1.y += 1;
	}
}
int		get_dist(t_vec2 p1, t_vec2 p2)
{
	return (p2.y - p1.y);
}

void	draw_line(t_cub *cub, t_vec2 p1, t_vec2 p2)
{
	if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
	{
		if (p1.x > p2.x)
			line_low(cub, (t_vec2){p2.x, p2.y, p2.color},
				(t_vec2){p1.x, p1.y, p1.color}, get_dist(p1, p2));
		else
			line_low(cub, (t_vec2){p1.x, p1.y, p1.color},
				(t_vec2){p2.x, p2.y, p2.color}, get_dist(p1, p2));
	}
	else
	{
		if (p1.y > p2.y)
			line_high(cub, (t_vec2){p2.x, p2.y, p2.color},
				(t_vec2){p1.x, p1.y, p1.color}, get_dist(p1, p2));
		else
			line_high(cub, (t_vec2){p1.x, p1.y, p1.color},
				(t_vec2){p2.x, p2.y, p2.color}, get_dist(p1, p2));
	}
}
