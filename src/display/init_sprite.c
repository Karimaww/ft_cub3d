#include "cub3d.h"

int	sprite_text(t_cub **cub)
{
	(*cub)->sprite->text.win = NULL;
	(*cub)->sprite->text.img = mlx_xpm_file_to_image((*cub)->mlx.mlx,
			"sprites/barrel.xpm", &(*cub)->sprite->text.win_size.x,
			&(*cub)->sprite->text.win_size.y);
	if (!(*cub)->sprite->text.img)
		return (EXIT_FAILURE);
	(*cub)->sprite->text.addr = mlx_get_data_addr((*cub)->sprite->text.img,
			&((*cub)->sprite->text.bpp),
			&((*cub)->sprite->text.linel), &((*cub)->sprite->text.endian));
	return (EXIT_SUCCESS);
}

int	init_sprite(t_cub **cub)
{
	(*cub)->sprite = malloc(sizeof(t_sprite));
	if (!(*cub)->sprite)
		return (EXIT_FAILURE);
	(*cub)->sprite->z_buf = malloc(sizeof(double) * (*cub)->mlx.win_size.x);
	if (!(*cub)->sprite->z_buf)
		return (EXIT_FAILURE);
	ft_bzero((*cub)->sprite->z_buf, (*cub)->mlx.win_size.x);
	(*cub)->sprite->pos.x = 5;
	(*cub)->sprite->pos.y = 5;
	return (EXIT_SUCCESS);
}
