/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:16 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:16:16 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This is the game loop, in order for the sprites to be animated, it
 * checks if the game has gone through the loop 5 times and then it changes the
 * texture (to get the next frame of the animation).
 * @param cub
 */
int	update_game(t_cub *cub)
{
	draw_back(cub, &(cub->ray));
	if (cub->press->w)
		forward(cub);
	if (cub->press->a)
		left(cub);
	if (cub->press->s)
		back(cub);
	if (cub->press->d)
		right(cub);
	if (cub->press->rl)
		rot_left(cub, 1.0);
	if (cub->press->rr)
		rot_right(cub, 1.0);
	if (draw_cub(cub, cub->ray) == EXIT_FAILURE)
		return (ft_close(cub), 1);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}
