/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:20 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:16:20 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx(t_cub **cub)
{
	t_cub	*c;

	c = *cub;
	c->mlx.mlx = mlx_init();
	if (!c->mlx.mlx)
		return (EXIT_FAILURE);
	c->mlx.win = mlx_new_window(c->mlx.mlx, c->mlx.win_size.x,
			c->mlx.win_size.y, "CUB3D");
	if (!c->mlx.win)
		return (EXIT_FAILURE);
	c->mlx.img = mlx_new_image(c->mlx.mlx, c->mlx.win_size.x,
			c->mlx.win_size.y);
	if (!c->mlx.img)
		return (EXIT_FAILURE);
	c->mlx.addr = mlx_get_data_addr(c->mlx.img, &(c->mlx.bpp),
			&(c->mlx.linel), &(c->mlx.endian));
	return (EXIT_SUCCESS);
}

/**
 * @brief Init the ray: pos.x and pos.y are the starting position.
 * dir.x and dir.y is the initial direction vector.
 * The rest are the 2D version of the camera plane. 
 * @param ray 
 * @param cub 
 * @return int 
 */
static int	init_ray(t_ray **ray, t_cub *cub)
{
	*ray = malloc(sizeof(t_ray));
	if (!*ray)
		return (printf("Error\nMalloc of t_ray.\n"), EXIT_FAILURE);
	cub->ray = *ray;
	(*ray)->pos.x = cub->map->player.x + 0.5;
	(*ray)->pos.y = cub->map->player.y + 0.5;
	(*ray)->dir.x = -1;
	(*ray)->dir.y = 0;
	(*ray)->camera_x = 0;
	(*ray)->plane.x = 0;
	(*ray)->plane.y = 0.66;
	init_rot(cub);
	return (EXIT_SUCCESS);
}

static int	init_cub_first(t_cub **c, t_map *map)
{
	t_cub	*cub;

	cub = *c;
	cub->mlx.win_size.x = 1200;
	cub->mlx.win_size.y = 800;
	cub->map = map;
	return (EXIT_SUCCESS);
}

/**
 * @brief Init all the parameters of cub and of the mlx (with init_mlx)
 * Use mlx_mouse_hide(cub->mlx.mlx, cub->mlx.win); for prettier results
 * We did not use it during evaluation since it leaks.
 * mlx_do_key_autorepeatoff for smoother movement
 * @param map 
 * @return t_cub* 
 */
t_cub	*init_cub(t_map *map)
{
	t_cub	*cub;
	t_ray	*ray;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	if (init_cub_first(&cub, map) == EXIT_FAILURE || init_press(&cub) == 1)
		return (ft_close(cub), NULL);
	ray = NULL;
	cub->ray = ray;
	if (init_mlx(&cub) == EXIT_FAILURE)
		return (ft_close(cub), NULL);
	mlx_do_key_autorepeatoff(cub->mlx.mlx);
	if (init_textures(&cub) == EXIT_FAILURE || init_ray(&ray, cub) == 1)
		return (ft_close(cub), NULL);
	mlx_hook(cub->mlx.win, DestroyNotify, KeyPressMask, mouse_hook, cub);
	mlx_hook(cub->mlx.win, KeyPress, KeyPressMask, ft_key_choose, cub);
	mlx_hook(cub->mlx.win, KeyRelease, KeyReleaseMask, change_flag_0, cub);
	mlx_loop_hook(cub->mlx.mlx, &update_game, cub);
	return (cub);
}
