/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:18 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:16:18 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Press is a strcture that allows for a smoother rendering of the game
 * and to press 2 or more keys at the same time.
 * It works in par with mlx_do_key_autorepeatoff(cub->mlx.mlx)
 * @param cub
 */
int	init_press(t_cub **cub)
{
	(*cub)->press = malloc(sizeof(t_press));
	if (!(*cub)->press)
		return (printf("Error\nMalloc of t_press."), EXIT_FAILURE);
	(*cub)->press->w = 0;
	(*cub)->press->a = 0;
	(*cub)->press->s = 0;
	(*cub)->press->d = 0;
	(*cub)->press->rl = 0;
	(*cub)->press->rr = 0;
	return (EXIT_SUCCESS);
}

/**
 * @brief This function is for the KeyRelease hook, it allows for smoother
 * graphics by disabling auto-repeat.
 * @param key 
 * @param cub 
 * @return int 
 */
int	change_flag_0(int key, t_cub *cub)
{
	if (key == W)
		cub->press->w = 0;
	if (key == A)
		cub->press->a = 0;
	if (key == S)
		cub->press->s = 0;
	if (key == D)
		cub->press->d = 0;
	if (key == RL)
		cub->press->rl = 0;
	if (key == RR)
		cub->press->rr = 0;
	return (0);
}
