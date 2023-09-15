/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:05 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:05 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->square_size)
	{
		j = 0;
		while (j < cub->square_size)
		{
			pixel_put(&(cub->mlx), x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_player_triangle(t_cub *cub, int x, int y, int scale)
{
	t_vec2	tip;
	t_vec2	base1;
	t_vec2	base2;

	tip.x = (int)(x + cub->ray->dir.x * scale);
	tip.y = (int)(y + cub->ray->dir.y * scale);
	tip.color = RGB_RED;
	base1.x = (int)(x + (cub->ray->plane.x * scale / 2));
	base1.y = (int)(y + (cub->ray->plane.y * scale / 2));
	base1.color = RGB_RED;
	base2.x = (int)(x - (cub->ray->plane.x * scale / 2));
	base2.y = (int)(y - (cub->ray->plane.y * scale / 2));
	base2.color = RGB_RED;
	draw_line(cub, tip, base1);
	draw_line(cub, tip, base2);
	draw_line(cub, base1, base2);
}

static void	draw_obj(t_cub *cub, t_vec2 map, t_vec2 i, t_vec2 start)
{
	char	map_cell;

	map_cell = cub->map->map[map.y][map.x];
	if (map_cell == '1')
		draw_square(cub, i.x, i.y, DARK_BLUE);
	else if (map_cell == '2')
		draw_square(cub, i.x, i.y, RGB_SKY);
	else if (map_cell == '0'
		|| map_cell == '3' || map_cell == 'W' || map_cell == 'E'
		|| map_cell == 'N' || map_cell == 'S')
		draw_square(cub, i.x, i.y, GREY);
	i.x = (cub->ray->pos.x - start.x + MAP_X_OFFSET) * MAP_SCALE;
	i.y = (cub->ray->pos.y - start.y + MAP_Y_OFFSET) * MAP_SCALE;
	draw_player_triangle(cub, i.x, i.y, MAP_SCALE);
}

static void	check_start(t_cub *cub, int *x, int *y)
{
	*x = cub->ray->pos.x - MAP_SIZE_X / 2;
	*y = cub->ray->pos.y - MAP_SIZE_Y / 2;
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	if (*x + MAP_SIZE_X > cub->map->map_size.x)
		*x = cub->map->map_size.x - MAP_SIZE_X;
	if (*y + MAP_SIZE_Y > cub->map->map_size.y)
		*y = cub->map->map_size.y - MAP_SIZE_Y;
}

void	draw_minimap(t_cub *cub)
{
	t_vec2	i;
	t_vec2	pos;
	t_vec2	start;
	t_vec2	map;

	pos.x = 0;
	pos.y = 0;
	check_start(cub, &(start.x), &(start.y));
	while (pos.y < MAP_SIZE_Y)
	{
		pos.x = -1;
		while (++pos.x < MAP_SIZE_X)
		{
			map.x = start.x + pos.x;
			map.y = start.y + pos.y;
			i.x = (pos.x + MAP_X_OFFSET) * MAP_SCALE;
			i.y = (pos.y + MAP_Y_OFFSET) * MAP_SCALE;
			if (map.y < 0 || map.y >= cub->map->map_size.y
				|| map.x < 0 || map.x >= cub->map->map_size.x)
				continue ;
			draw_obj(cub, map, i, start);
		}
		pos.y++;
	}
}
