#include "cub3d.h"

void	draw_player_triangle(t_cub *cub, int x, int y, int scale)
{
	// int i;
	// int length = 15; // Length of the triangle sides
	t_vec2	tip;
	t_vec2	base1;
	t_vec2	base2;

	// Scale the map_dir and map_plane vectors to minimap scale
	double dir_x = cub->ray->dir.x * scale;
	double dir_y = cub->ray->dir.y * scale;
	double plane_x = cub->ray->plane.x * scale;
	double plane_y = cub->ray->plane.y * scale;

	tip.x = x + (int)dir_x;
	tip.y = y + (int)dir_y;
	tip.color = RGB_RED;

	// Calculate points for the base of the triangle
	base1.x = x + (int)(plane_x / 2);
	base1.y = y + (int)(plane_y / 2);
	base1.color = RGB_RED;

	base2.x = x - (int)(plane_x / 2);
	base2.y = y - (int)(plane_y / 2);
	base2.color = RGB_RED;

	// // Draw the triangle by connecting the points
	draw_line(cub, tip, base1);
	draw_line(cub, tip, base2);
	draw_line(cub, base1, base2);
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	draw_minimap(t_cub *cub)
{
	int x;
	int y;
	int xi;
	int yi;
	int minimap_x_offset = 10;
	int minimap_y_offset = 10;
	int minimap_scale = 10;
	int minimap_size_x = 17; // Adjust this to change the minimap size
	int minimap_size_y = 11;  // Adjust this to change the minimap size

	// Calculate the starting position of the minimap based on player's position
	int start_x = cub->ray->pos.x - minimap_size_x / 2;
	int start_y = cub->ray->pos.y - minimap_size_y / 2;

	// Ensure the minimap view stays within the map boundaries
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (start_x + minimap_size_x > cub->map->map_size.x)
		start_x = cub->map->map_size.x - minimap_size_x;
	if (start_y + minimap_size_y > cub->map->map_size.y)
		start_y = cub->map->map_size.y - minimap_size_y;

	for (y = 0; y < minimap_size_y; y++)
	{
		for (x = 0; x < minimap_size_x; x++)
		{
			int map_x = start_x + x;
			int map_y = start_y + y;

			xi = (x + minimap_x_offset) * minimap_scale;
			yi = (y + minimap_y_offset) * minimap_scale;

			if (map_y < 0 || map_y >= cub->map->map_size.y
				|| map_x < 0 || map_x >= cub->map->map_size.x)
				continue ;
			char map_cell = cub->map->map[map_y][map_x];

			// Draw the map cells based on their content
			if (map_cell == '1')
				draw_square(cub, xi, yi, DARK_BLUE);
			else if (map_cell == '2')
				draw_square(cub, xi, yi, RGB_SKY);
			else if (map_cell == '0'
				|| map_cell == '3' || map_cell == 'W' || map_cell == 'E'
				|| map_cell == 'N' || map_cell == 'S')
				draw_square(cub, xi, yi, GREY);
			// Calculate the position of the player on the minimap
			xi = (cub->ray->pos.x - start_x + minimap_x_offset) * minimap_scale;
			yi = (cub->ray->pos.y - start_y + minimap_y_offset) * minimap_scale;
			// draw_square(cub, xi, yi, RGB_RED);
			draw_player_triangle(cub, xi, yi, minimap_scale);
		}
	}
}

// void    draw_minimap(t_cub *cub)
// {
//     int    x;
//     int    y;
//     int    xi;
//     int    yi;
//     int    minimap_x_offset = 10;
//     int    minimap_y_offset = 10;
//     int    minimap_scale = 10;
//     int    radius = 50;
//     int    xmin = ft_max(0, cub->ray->pos.x - radius);
//     int    xmax = ft_min(cub->map->map_size.x, cub->ray->pos.x + radius);
//     int    ymin = ft_max(0, cub->ray->pos.y - radius);
//     int    ymax = ft_min(cub->map->map_size.y, cub->ray->pos.y + radius);
//     printf("xmin : %d, xmax : %d, ymin : %d, ymax : %d\n", xmin, xmax, ymin, ymax);

//     y = ymin;
//     while (y < ymax)
//     {
//         x = xmin;
//         while (x < xmax)
//         {
//             // xi = x *  cub->mlx.win_size.x / cub->map->map_size.x / 5;
//             // yi = y * cub->mlx.win_size.y / cub->map->map_size.y / 5;
//             // xi = cub->mlx.win_size.x - minimap_x_offset - (cub->map->map_size.x - x) * minimap_scale;
//             // yi = cub->mlx.win_size.y - minimap_y_offset - (cub->map->map_size.y - y) * minimap_scale;
// 			xi = (cub->map->map_size.x - x) * minimap_scale;
//             yi = (cub->map->map_size.y - y) * minimap_scale;
// 			printf("xi : %d yi : %d\n", xi, yi);
//             if (cub->map->map[y][x] == '0'
//                 || cub->map->map[y][x] == '3')
//                 draw_square(cub, xi , yi, 0x00FFFF);
//             else if (cub->map->map[y][x] == '1')
//                 draw_square(cub, xi, yi, 0xF0F00);
//             else if (cub->map->map[y][x] == '2')
//                 draw_square(cub, xi, yi, 0x0000FF);
//             // if (xi == cub->sprite[0].initial_pos.x && yi == cub->sprite[0].initial_pos.y)
//             //     draw_square(cub, xi, yi, 0x0000FF);
//             //if (yi == cub->ray->pos.y && xi == cub->ray->pos.x)
//             //     draw_square(cub, xi, yi, 0xFF0000);
//             x++;
//         }
//         y++;
//     }
//     int square = cub->square_size;
//     cub->square_size = 5;
// 	draw_player_triangle(cub, cub->mlx.win_size.x - minimap_x_offset - (cub->map->map_size.x - cub->ray->pos.x) * minimap_scale, cub->mlx.win_size.y - minimap_y_offset - (cub->map->map_size.y - cub->ray->pos.y) * minimap_scale, minimap_scale);
//     // draw_square(cub, cub->mlx.win_size.x - minimap_x_offset - (cub->map->map_size.x - cub->ray->pos.x) * minimap_scale, cub->mlx.win_size.y - minimap_y_offset - (cub->map->map_size.y - cub->ray->pos.y) * minimap_scale, 0xFF0000);
//     cub->square_size = square;
// }

static void	sort_sprites(t_cub *cub)
{
	int	i;
	int	j;
	t_sprite tmp;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		cub->sprite[i].dist = ((cub->ray->pos.x - cub->sprite[i].initial_pos.x)
			* (cub->ray->pos.x - cub->sprite[i].initial_pos.x)
			+ (cub->ray->pos.y - cub->sprite[i].initial_pos.y)
			* (cub->ray->pos.y - cub->sprite[i].initial_pos.y)); 
		++i;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		j = i + 1;
		while (j < SPRITE_COUNT)
		{
			if (cub->sprite[i].dist < cub->sprite[j].dist)
			{
				tmp = cub->sprite[i];
				cub->sprite[i] = cub->sprite[j];
				cub->sprite[j] = tmp;
			}
			++j;
		}
		++i;
	}
}
int	draw_cub(t_cub *cub, t_ray *ray)
{
	int	x;

	x = 0;
	draw_back(cub, &ray);
	while (x < cub->mlx.win_size.x)
	{
		init_raydir(&ray, cub, x);
		init_side_dist(&ray);
		dda_algo(&ray, cub);
		show_line(&ray, cub, x);
		cub->z_buf[x] = ray->perp_dist;
		x++;
	}
	sort_sprites(cub);
	x = 0;
	while (x < SPRITE_COUNT)
	{
		cub->sprite[x].pos.x = cub->sprite[x].initial_pos.x;
		cub->sprite[x].pos.y = cub->sprite[x].initial_pos.y;
		draw_sprite(&cub, ray, &(cub->sprite[x]));
		x++;
	}
	draw_minimap(cub);
	return (EXIT_SUCCESS);
}
