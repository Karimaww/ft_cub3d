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
	(*ray)->pos.x = cub->map->player.x;
	(*ray)->pos.y = cub->map->player.y;
	//initial direction vector
	(*ray)->dir.x = -1;
	(*ray)->dir.y = 0;
	//the 2d raycaster version of camera plane
	(*ray)->camera_x = 0;
	//the 2d raycaster version of camera plane//the 2d raycaster version of camera plane
	(*ray)->plane.x = 0;
	(*ray)->plane.y = 0.66;
	return (EXIT_SUCCESS);
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
	if (init_mlx(&cub) == EXIT_FAILURE)
		return (NULL);
	cub->texture = init_textures(cub);
	if (!cub->texture)
		return (printf("\nHERE\n"), NULL);
	ray = NULL;
	if (init_ray(&ray, cub) == EXIT_FAILURE)
		return (NULL);
	if (draw_cub(cub, ray) == EXIT_FAILURE)
		return (NULL);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	mlx_hook(cub->mlx.win, ON_DESTROY, MKEYPRESS, mouse_hook, cub);
	mlx_hook(cub->mlx.win, ON_KEYDOWN, MKEYPRESS, ft_key_choose, cub);
	//mlx_loop(cub->mlx.mlx);
	return (cub);
}
