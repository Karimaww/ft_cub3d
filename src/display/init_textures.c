#include "cub3d.h"

// faut check si xpm_to_image/get_data_addr est NULL??
t_txt	*init_textures(t_cub *cub)
{
	t_txt	*text;

	text = malloc(sizeof(t_txt));
	if (!text)
		return (NULL);
	printf("MAP NORTH : [%s]\n", cub->map->no);
	text->north.img = mlx_xpm_file_to_image(&(cub->mlx), cub->map->no,
			&text->north.win_size.x, &text->north.win_size.y);
	if (!text->north.img)
		return (free(text), NULL);
	text->north.addr = mlx_get_data_addr(text->north.img, &(text->north.bpp),
			&(text->north.linel), &(text->north.endian));

	text->south.img = mlx_xpm_file_to_image(&(cub->mlx), cub->map->so,
			&text->south.win_size.x, &text->south.win_size.y);
	text->south.addr = mlx_get_data_addr(text->south.img, &(text->south.bpp),
			&(text->south.linel), &(text->south.endian));

	text->west.img = mlx_xpm_file_to_image(&(cub->mlx), cub->map->we,
			&text->west.win_size.x, &text->west.win_size.y);
	text->west.addr = mlx_get_data_addr(text->west.img, &(text->west.bpp),
			&(text->west.linel), &(text->west.endian));

	text->east.img = mlx_xpm_file_to_image(&(cub->mlx), cub->map->ea,
			&text->east.win_size.x, &text->east.win_size.y);
	text->east.addr = mlx_get_data_addr(text->east.img, &(text->east.bpp),
			&(text->east.linel), &(text->east.endian));
	return (text);
}
