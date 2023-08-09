#include "cub3d.h"

int	init_mlx(t_cub **cub)
{
	t_cub	*c;

	c = cub;
	c->mlx->mlx = mlx_init();
	if (!c->mlx->mlx)
		return (EXIT_FAILURE);
	c->mlx->win = mlx_new_window(c->mlx->mlx, c->mlx->win_size.x,
			c->mlx->win_size.y, "CUB3D");
	if (!c->mlx->win)
		return (EXIT_FAILURE);
	c->mlx->img = mlx_new_image(c->mlx->mlx, c->mlx->win_size.x,
			c->mlx->win_size.y);
	if (!c->mlx->img)
		return (EXIT_FAILURE);
	c->mlx->addr = mlx_get_data_addr(c->mlx->img, &(c->mlx->bpp),
			&(c->mlx->linel), &(c->mlx->endian));
}

t_cub	*init_cub(t_map *map)
{
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->map = map;
	cub->mlx->win_size.x = 1200;
	cub->mlx->win_size.y = 800;
	if (init_mlx(&cub) == EXIT_FAILURE)
		return (NULL);
	//fdf->theme = &default_theme;
	//init_view(fdf);
	if (draw_cub(cub) == EXIT_FAILURE)
		return (NULL);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	mlx_hook(cub->mlx->win, ON_DESTROY, MKEYPRESS, mouse_hook, cub);
	mlx_hook(cub->mlx->win, ON_KEYDOWN, MKEYPRESS, ft_key_choose, cub);
	return (cub);
}