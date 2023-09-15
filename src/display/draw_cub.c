/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:08 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:16:08 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		x++;
	}
	return (EXIT_SUCCESS);
}
