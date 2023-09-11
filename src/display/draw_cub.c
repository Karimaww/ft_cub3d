#include "cub3d.h"

void	draw_minimap2(t_cub *cub)
{
	int	x;
	int	y;
	int	xi;
	int yi;

	x = 0;
	y = 0;
	while (y < cub->mlx.win_size.y / 4)
	{
		y = 0;
		while (x < cub->mlx.win_size.x / 3)
		{
			yi = (int)(y * cub->map->map_size.y / cub->mlx.win_size.y);
			xi = (int)(x * cub->map->map_size.x / cub->mlx.win_size.x);
			if (cub->map->map[yi][xi] == '0'
				|| cub->map->map[yi][xi] == '3'
				|| cub->map->map[yi][xi] == ' ')
				draw_square(cub, x, y, 0x00FFFF);
			else if (cub->map->map[yi][xi] == '1')
				draw_square(cub, x, y, 0xF0F00);
			else if (cub->map->map[yi][xi] == '2')
				draw_square(cub, x, y, 0x0000FF);
			else if (yi == cub->ray->pos.y && xi == cub->ray->pos.x)
				draw_square(cub, x, y, 0xFF0000);
			y += cub->square_size;
		}
		x += cub->square_size;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	x;
	int	y;
	int	xi;
	int	yi;

	y = 0;
	while (y < cub->map->map_size.y)
	{
		x = 0;
		while (x < cub->map->map_size.x)
		{
			xi = x *  cub->mlx.win_size.x / cub->map->map_size.x / 5;
			yi = y * cub->mlx.win_size.y / cub->map->map_size.y / 5;
			if (cub->map->map[y][x] == '0'
				|| cub->map->map[y][x] == '3'
				|| cub->map->map[y][x] == ' ')
				draw_square(cub, xi , yi, 0x00FFFF);
			else if (cub->map->map[y][x] == '1')
				draw_square(cub, xi, yi, 0xF0F00);
			else if (cub->map->map[y][x] == '2')
				draw_square(cub, xi, yi, 0x0000FF);
			else if (yi == cub->ray->pos.y && xi == cub->ray->pos.x)
				draw_square(cub, xi, yi, 0xFF0000);
			x++;
		}
		y++;
	}

}

// void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
// {
//     int i, j;
//     for(i = 0; i < size; i++)
//     {
//         for(j = 0; j < size; j++)
//         {
//             mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
//         }
//     }
// }

int	draw_cub(t_cub *cub, t_ray *ray)
{
	int	x;

	x = 0;
	// Floor casting
	draw_back(cub, &ray);
	// Wall casting
	while (x < cub->mlx.win_size.x)
	{
		init_raydir(&ray, cub, x);
		//calculate step and initial sideDist
		init_side_dist(&ray);
		dda_algo(&ray, cub);
		show_line(&ray, cub, x);
		cub->z_buf[x] = ray->perp_dist;
		x++;
	}
	// Sprite casting
	x = 0;
	while (x < SPRITE_COUNT)
	{
		cub->sprite[x].pos.x = cub->sprite[x].initial_pos.x;
		cub->sprite[x].pos.y = cub->sprite[x].initial_pos.y;
		draw_sprite(&cub, ray, &(cub->sprite[x]));
		x++;
	}
	draw_minimap(cub);
	// draw_square(cub->mlx.mlx, cub->mlx.win, 10, 10, 100, 0x00FFFF);
	return (EXIT_SUCCESS);
}
