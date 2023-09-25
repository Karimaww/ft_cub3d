/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:00 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:00 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Sort the sprites in order of distance so that if you look at one 
 * sprite through the over it will only show the sprite closest to you.
 * @param cub 
 */
static void	sort_sprites(t_cub *cub)
{
	int			i;
	int			j;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		cub->sprite[i].dist = ((cub->ray->pos.x - cub->sprite[i].initial_pos.x)
				* (cub->ray->pos.x - cub->sprite[i].initial_pos.x)
				+ (cub->ray->pos.y - cub->sprite[i].initial_pos.y)
				* (cub->ray->pos.y - cub->sprite[i].initial_pos.y));
		++i;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		j = i + 1;
		while (j < SPRITE_COUNT)
		{
			if (cub->sprite[i].dist < cub->sprite[j].dist)
				swap_sprites(&(cub->sprite[i]), &(cub->sprite[j]));
			++j;
		}
		++i;
	}
}

int	draw_cub(t_cub *cub, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < cub->mlx.win_size.x)
	{
		init_raydir(&ray, cub, x);
		init_side_dist(&ray);
		dda_algo(&ray, cub);
		show_line(&ray, cub, x);
		cub->z_buf[x] = ray->perp_dist;
		x++;
	}
	sort_sprites(cub);
	x = 0;
	while (x < SPRITE_COUNT)
	{
		cub->sprite[x].pos.x = cub->sprite[x].initial_pos.x;
		cub->sprite[x].pos.y = cub->sprite[x].initial_pos.y;
		draw_sprite(&cub, ray, &(cub->sprite[x]));
		x++;
	}
	draw_minimap(cub);
	return (EXIT_SUCCESS);
}
