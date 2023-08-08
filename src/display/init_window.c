#include "cub3d.h"

int	init_mlx(t_cub **cub)
{
	t_cub	*c;

	c = cub;
	c->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		return (EXIT_FAILURE);
	c->mlx.win = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x,
			fdf->mlx.win_size.y, "FDF");
	if (!c->mlx.win)
		return (EXIT_FAILURE);
	c->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->mlx.win_size.x,
			fdf->mlx.win_size.y);
	if (!c->mlx.img)
		return (EXIT_FAILURE);
	c->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp),
			&(fdf->mlx.linel), &(fdf->mlx.endian));
}

t_cub	*init_cub(t_map *map)
{
	t_cub	*fdf;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->map = map;
	cub->mlx.win_size.x = 1200;
	cub->mlx.win_size.y = 800;
	if (init_mlx(&cub) == EXIT_FAILURE)
		return (NULL);
	//fdf->theme = &default_theme;
	//init_view(fdf);
	if (draw_cub(cub) == EXIT_FAILURE)
		return (NULL);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	mlx_hook(fdf->mlx.win, ON_DESTROY, MKEYPRESS, mouse_hook, fdf);
	mlx_hook(fdf->mlx.win, ON_KEYDOWN, MKEYPRESS, ft_key_choose, fdf);
	return (fdf);
}