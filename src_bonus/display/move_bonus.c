/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:25 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:25 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Below are some functions to deal with hooks it checks if there is a
 * door and if the door is open or if a wall was found.
 * @param cub
 */
void	forward(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x + cub->ray->dir.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.x += cub->ray->dir.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y + cub->ray->dir.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.y += cub->ray->dir.y * SPEED;
}

void	back(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x - cub->ray->dir.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.x -= cub->ray->dir.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y - cub->ray->dir.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.y -= cub->ray->dir.y * SPEED;
}

void	left(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x + cub->ray->plane.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.x += cub->ray->plane.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y + cub->ray->plane.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.y += cub->ray->plane.y * SPEED;
}

void	right(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x - cub->ray->plane.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.x -= cub->ray->plane.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y - cub->ray->plane.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[y][x] != '2'
		&& cub->map->map[y][x] != '1')
		cub->ray->pos.y -= cub->ray->plane.y * SPEED;
}

void	open_door(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x + cub->ray->dir.x);
	y = (int)(cub->ray->pos.y + cub->ray->dir.y);
	if (x >= 0 && x < cub->map->map_size.x
		&& y >= 0 && y < cub->map->map_size.y
		&& cub->map->map[y][x] == '2')
		cub->map->map[y][x] = '3';
	else if (x >= 0 && x < cub->map->map_size.x
		&& y >= 0 && y < cub->map->map_size.y
		&& cub->map->map[y][x] == '3')
		cub->map->map[y][x] = '2';
	return ;
}
