#include "cub3d.h"

void	text_addr(t_cub **cub)
{
	(*cub)->north.addr = mlx_get_data_addr((*cub)->north.img,
			&((*cub)->north.bpp),
			&((*cub)->north.linel), &((*cub)->north.endian));
	(*cub)->south.addr = mlx_get_data_addr((*cub)->south.img,
			&((*cub)->south.bpp),
			&((*cub)->south.linel), &((*cub)->south.endian));
	(*cub)->west.addr = mlx_get_data_addr((*cub)->west.img, &((*cub)->west.bpp),
			&((*cub)->west.linel), &((*cub)->west.endian));
	(*cub)->east.addr = mlx_get_data_addr((*cub)->east.img, &((*cub)->east.bpp),
			&((*cub)->east.linel), &((*cub)->east.endian));
	(*cub)->door.addr = mlx_get_data_addr((*cub)->door.img, &((*cub)->door.bpp),
			&((*cub)->door.linel), &((*cub)->door.endian));
}

int	init_textures(t_cub **cub)
{
	(*cub)->north.mlx = NULL;
	(*cub)->south.mlx = NULL;
	(*cub)->west.mlx = NULL;
	(*cub)->east.mlx = NULL;
	(*cub)->door.mlx = NULL;
	(*cub)->north.win = NULL;
	(*cub)->south.win = NULL;
	(*cub)->west.win = NULL;
	(*cub)->east.win = NULL;
	(*cub)->door.win = NULL;
	(*cub)->north.img = mlx_xpm_file_to_image((*cub)->mlx.mlx, (*cub)->map->no,
			&(*cub)->north.win_size.x, &(*cub)->north.win_size.y);
	(*cub)->south.img = mlx_xpm_file_to_image((*cub)->mlx.mlx, (*cub)->map->so,
			&(*cub)->south.win_size.x, &(*cub)->south.win_size.y);
	(*cub)->west.img = mlx_xpm_file_to_image((*cub)->mlx.mlx, (*cub)->map->we,
			&(*cub)->west.win_size.x, &(*cub)->west.win_size.y);
	(*cub)->east.img = mlx_xpm_file_to_image((*cub)->mlx.mlx, (*cub)->map->ea,
			&(*cub)->east.win_size.x, &(*cub)->east.win_size.y);
	(*cub)->door.img = mlx_xpm_file_to_image((*cub)->mlx.mlx, "textures-mineraux/door.xpm",
			&(*cub)->door.win_size.x, &(*cub)->door.win_size.y);
	if (!(*cub)->north.img || !(*cub)->south.img
		|| !(*cub)->west.img || !(*cub)->east.img || !(*cub)->door.img)
		return (printf("Failed to open .xpm file\n"), EXIT_FAILURE);
	// printf("text w : %d h %d\n", (*cub)->west.win_size.x, (*cub)->west.win_size.y);
	return (text_addr(cub), EXIT_SUCCESS);
}
