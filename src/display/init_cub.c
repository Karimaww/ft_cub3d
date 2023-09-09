#include "cub3d.h"

int	init_mlx(t_cub **cub)
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

int	init_ray(t_ray **ray, t_cub *cub)
{
	*ray = malloc(sizeof(t_ray));
	if (!*ray)
		return (printf("Error : Malloc of t_ray.n"), EXIT_FAILURE);
	cub->ray = *ray;
	//x and y start position
	(*ray)->pos.x = cub->map->player.x + 0.5;
	(*ray)->pos.y = cub->map->player.y + 0.5;
	//initial direction vector
	(*ray)->dir.x = -1;
	(*ray)->dir.y = 0;
	//the 2d raycaster version of camera plane
	(*ray)->camera_x = 0;
	//the 2d raycaster version of camera plane//the 2d raycaster version of camera plane
	(*ray)->plane.x = 0;
	(*ray)->plane.y = 0.66;
	init_rot(cub);
	return (EXIT_SUCCESS);
}

/**
 * @brief Press is a strcture that allows for a smoother rendering of the game
 * and to press 2 or more keys at the same time.
 * It works in par with mlx_do_key_autorepeatoff(cub->mlx.mlx)
 * @param cub
 */
void	init_press(t_cub **cub)
{
	(*cub)->press = malloc(sizeof(t_press));
	if (!(*cub)->press)
		return ;
	(*cub)->press->w = 0;
	(*cub)->press->a = 0;
	(*cub)->press->s = 0;
	(*cub)->press->d = 0;
	(*cub)->press->rl = 0;
	(*cub)->press->rr = 0;
}

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

/**
 * @brief This is the game loop, in order for the sprites to be animated, it
 * checks if the game has gone through the loop 5 times and then it changes the
 * texture (to get the next frame of the animation).
 * @param cub
 */
int	update_game(t_cub *cub)
{
	int	i;

	i = 0;
	cub->frame_counter++;
	if (cub->frame_counter >= 5)
	{
		cub->frame_counter = 0;
		while (i < SPRITE_COUNT)
		{
			cub->sprite[i].current_frame = (cub->sprite[i].current_frame + 1)
				% cub->sprite[i].text_count;
			cub->sprite[i].text_id = cub->sprite[i].current_frame;
			i++;
		}
	}
	clear_screen(cub);
	if (cub->press->w)
		forward(cub);
	if (cub->press->a)
		left(cub);
	if (cub->press->s)
		back(cub);
	if (cub->press->d)
		right(cub);
	if (cub->press->rl)
		rot_left(cub);
	if (cub->press->rr)
		rot_right(cub);
	if (draw_cub(cub, cub->ray) == EXIT_FAILURE)
		return (ft_close(cub), 1);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}

// remettre la souris au milieu
int		handle_mouse(int x, int y, t_cub *cub)
{
	int	new_x;

	(void)y;
	new_x = x - (cub->mlx.win_size.x / 2);
	if (new_x < 0)
	{
		// cub->press->rl = 1;
		// cub->press->rr = 0;
		rot_left(cub);
	}
	else
	{
		// cub->press->rl = 0;
		// cub->press->rr = 1;
		rot_right(cub);
	}
	return (0);
}

t_cub	*init_cub(t_map *map)
{
	t_cub	*cub;
	t_ray	*ray;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->map = map;
	cub->mlx.win_size.x = 1200;
	cub->mlx.win_size.y = 800;
	cub->z_buf = malloc(sizeof(double) * cub->mlx.win_size.x);
	if (!cub->z_buf)
		return (ft_close(cub), NULL);
	ft_bzero(cub->z_buf, cub->mlx.win_size.x);
	init_press(&cub);
	ray = NULL;
	cub->sprite = NULL;
	cub->ray = ray;
	cub->frame_counter = 0;
	if (init_mlx(&cub) == EXIT_FAILURE)
		return (ft_close(cub), NULL);
	mlx_do_key_autorepeatoff(cub->mlx.mlx);
	if (init_textures(&cub) == EXIT_FAILURE)
		return (ft_close(cub), NULL);
	if (init_ray(&ray, cub) == EXIT_FAILURE)
		return (ft_close(cub), NULL);
	if (init_sprite(&cub) == EXIT_FAILURE)
		return (ft_close(cub), NULL);
	// if (draw_cub(cub, ray) == EXIT_FAILURE)
	// 	return (ft_close(cub), NULL);
	//mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	mlx_hook(cub->mlx.win, DestroyNotify, KeyPressMask, mouse_hook, cub);
	mlx_hook(cub->mlx.win, KeyPress, KeyPressMask, ft_key_choose, cub);
	mlx_hook(cub->mlx.win, KeyRelease, KeyReleaseMask, change_flag_0, cub);
	mlx_hook(cub->mlx.win, MotionNotify, PointerMotionMask, handle_mouse, cub);
	mlx_loop_hook(cub->mlx.mlx, &update_game, cub);
	// mlx_hook(cub->mlx.win, ON_DESTROY, MKEYPRESS, mouse_hook, cub);
	// mlx_hook(cub->mlx.win, KeyPress, KeyPressMask, ft_key_choose, cub);
	// mlx_hook(cub->mlx.win, KeyRelease, KeyReleaseMask, change_flag_0, cub);
	return (cub);
}
