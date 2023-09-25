/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stripe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:09 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/23 13:37:26 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	texture_on_img(t_mlx *texture, t_cub **cub, t_vec2 tex, t_vec2 val)
{
	int	r;
	int	g;
	int	b;

	if (!((tex.y >= 0 && tex.y < texture->win_size.y
				&& tex.x >= 0 && tex.x < texture->win_size.x)))
		return ;
	r = texture->addr[(int)(tex.y * texture->linel
			+ (double)tex.x * ((double)texture->bpp / 8))];
	g = texture->addr[(int)(tex.y * texture->linel
			+ (double)tex.x * ((double)texture->bpp / 8) + 1)];
	b = texture->addr[(int)(tex.y * texture->linel
			+ (double)tex.x * ((double)texture->bpp / 8) + 2)];
	if (r == 0 && g == 0 && b == 0)
		return ;
	(*cub)->mlx.addr[val.y * (*cub)->mlx.linel + val.x
		* (*cub)->mlx.bpp / 8] = r;
	(*cub)->mlx.addr[val.y * (*cub)->mlx.linel + val.x * ((*cub)->mlx.bpp / 8)
		+ 1] = g;
	(*cub)->mlx.addr[val.y * (*cub)->mlx.linel + val.x * ((*cub)->mlx.bpp / 8)
		+ 2] = b;
}

static void	get_wall_x(double *wall_x, t_ray **ray)
{
	if ((*ray)->side == 0)
		*wall_x = (*ray)->pos.y + (*ray)->perp_dist * (*ray)->ray_dir.y;
	else
		*wall_x = (*ray)->pos.x + (*ray)->perp_dist * (*ray)->ray_dir.x;
}

/**
 * @brief Draws a wal, step is how much to increase the texture coordinate
 * per screen pixel.
 * tex_pos is the starting texture coordinate and we cast the texture coordinate
 * to integer, and mask with (texHeight - 1) in case of overflow
 * @param side 
 * @param ray 
 * @param cub 
 * @param x 
 */
void	draw_side(t_mlx side, t_ray **ray, t_cub *cub, int x)
{
	t_vec2		val;
	t_vec2		tex;
	double		wall_x;
	double		step;
	double		tex_pos;

	val.x = x;
	get_wall_x(&wall_x, ray);
	wall_x -= floor(wall_x);
	tex.x = (int)(wall_x * (double)(side.win_size.x));
	if ((*ray)->side == 0 && (*ray)->ray_dir.x > 0)
		tex.x = side.win_size.x - tex.x - 1;
	if ((*ray)->side == 1 && (*ray)->ray_dir.y < 0)
		tex.x = side.win_size.x - tex.x - 1;
	step = 1.0 * side.win_size.y / (*ray)->line_h;
	tex_pos = ((*ray)->draw_start - cub->mlx.win_size.y / 2
			+ (*ray)->line_h / 2) * step;
	val.y = (*ray)->draw_start;
	while (val.y < (*ray)->draw_end)
	{
		tex_pos += step;
		tex.y = (int)tex_pos & (side.win_size.y - 1);
		texture_on_img(&side, &cub, tex, val);
		(val.y)++;
	}
}

void	draw_stripe(t_ray **ray, t_cub *cub, int x)
{
	if (cub->map->map[(*ray)->map.y][(*ray)->map.x] == '2')
		draw_side(cub->door, ray, cub, x);
	else if ((*ray)->side == 1 && (*ray)->ray_dir.y > 0)
		draw_side(cub->north, ray, cub, x);
	else if ((*ray)->side == 1 && (*ray)->ray_dir.y <= 0)
		draw_side(cub->south, ray, cub, x);
	else if ((*ray)->side == 0 && (*ray)->ray_dir.x > 0)
		draw_side(cub->west, ray, cub, x);
	else
		draw_side(cub->east, ray, cub, x);
}
