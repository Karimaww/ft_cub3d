/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:50 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:18:03 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_close(t_cub *cub)
{
	if (cub->map)
		free_map(cub->map);
	close_mlx(cub, cub->north);
	close_mlx(cub, cub->south);
	close_mlx(cub, cub->east);
	close_mlx(cub, cub->west);
	if (cub->press)
		free(cub->press);
	if (cub->ray)
	{
		free(cub->ray);
		cub->ray = NULL;
	}
	mlx_do_key_autorepeaton(cub->mlx.mlx);
	close_mlx(cub, cub->mlx);
	if (cub)
		free(cub);
	exit(0);
}

void	do_move(int key, t_cub *cub)
{
	if (key == W || cub->press->w == 1)
		cub->press->w = 1;
	if (key == A || cub->press->a == 1)
		cub->press->a = 1;
	if (key == S || cub->press->s == 1)
		cub->press->s = 1;
	if (key == D || cub->press->d == 1)
		cub->press->d = 1;
	if (key == RL || cub->press->rl == 1)
		cub->press->rl = 1;
	if (key == RR || cub->press->rr == 1)
		cub->press->rr = 1;
}

int	mouse_hook(t_cub *cub)
{
	ft_close(cub);
	return (0);
}

int	ft_key_choose(int key, t_cub *cub)
{
	if (key == ESC)
		ft_close(cub);
	do_move(key, cub);
	return (0);
}
