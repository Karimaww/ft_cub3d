#include "cub3d.h"

// void	draw_player_triangle(t_cub *cub, int x, int y, int scale)
// {
// 	t_vec2	tip;
// 	t_vec2	base1;
// 	t_vec2	base2;

// 	// Scale the map_dir and map_plane vectors to minimap scale
// 	double dir_x = cub->ray->dir.x * scale;
// 	double dir_y = cub->ray->dir.y * scale;
// 	double plane_x = cub->ray->plane.x * scale;
// 	double plane_y = cub->ray->plane.y * scale;

// 	tip.x = x + (int)dir_x;
// 	tip.y = y + (int)dir_y;
// 	tip.color = RGB_RED;

// 	// Calculate points for the base of the triangle
// 	base1.x = x + (int)(plane_x / 2);
// 	base1.y = y + (int)(plane_y / 2);
// 	base1.color = RGB_RED;

// 	base2.x = x - (int)(plane_x / 2);
// 	base2.y = y - (int)(plane_y / 2);
// 	base2.color = RGB_RED;

// 	// // Draw the triangle by connecting the points
// 	draw_line(cub, tip, base1);
// 	draw_line(cub, tip, base2);
// 	draw_line(cub, base1, base2);
// }
void	draw_player_triangle(t_cub *cub, int x, int y, int scale)
{
	t_vec2	tip;
	t_vec2	base1;
	t_vec2	base2;

	tip.x = (int)(x + cub->ray->dir.x * scale);
	tip.y = (int)(y + cub->ray->dir.y * scale);
	tip.color = RGB_RED;
	base1.x = (int)(x + (cub->ray->plane.x * scale / 2));
	base1.y = (int)(y + (cub->ray->plane.y * scale / 2));
	base1.color = RGB_RED;
	base2.x = (int)(x - (cub->ray->plane.x * scale / 2));
	base2.y = (int)(y - (cub->ray->plane.y * scale / 2));
	base2.color = RGB_RED;
	draw_line(cub, tip, base1);
	draw_line(cub, tip, base2);
	draw_line(cub, base1, base2);
}

void	draw_obj(t_cub *cub, t_vec2 map, t_vec2 i, t_vec2 start)
{
	char	map_cell;
	
	map_cell = cub->map->map[map.y][map.x];
	if (map_cell == '1')
		draw_square(cub, i.x, i.y, DARK_BLUE);
	else if (map_cell == '2')
		draw_square(cub, i.x, i.y, RGB_SKY);
	else if (map_cell == '0'
		|| map_cell == '3' || map_cell == 'W' || map_cell == 'E'
		|| map_cell == 'N' || map_cell == 'S')
		draw_square(cub, i.x, i.y, GREY);
	i.x = (cub->ray->pos.x - start.x + MAP_X_OFFSET) * MAP_SCALE;
	i.y = (cub->ray->pos.y - start.y + MAP_Y_OFFSET) * MAP_SCALE;
	draw_player_triangle(cub, i.x, i.y, MAP_SCALE);
}

// void	check_start(int *x, int *y)
// {
	
// }

void	draw_minimap(t_cub *cub)
{
	t_vec2	i;
	t_vec2	pos;
	t_vec2	start;
	t_vec2	map;

	pos.x = 0;
	pos.y = 0;
	start.x = cub->ray->pos.x - MAP_SIZE_X / 2;
	start.y = cub->ray->pos.y - MAP_SIZE_Y / 2;
	if (start.x < 0)
		start.x = 0;
	if (start.y < 0)
		start.y = 0;
	if (start.x + MAP_SIZE_X > cub->map->map_size.x)
		start.x = cub->map->map_size.x - MAP_SIZE_X;
	if (start.y + MAP_SIZE_Y > cub->map->map_size.y)
		start.y = cub->map->map_size.y - MAP_SIZE_Y;

	while (pos.y < MAP_SIZE_Y)
	{
		while (pos.x < MAP_SIZE_X)
		{
			map.x = start.x + pos.x;
			map.y = start.y + pos.y;

			i.x = (pos.x + MAP_X_OFFSET) * MAP_SCALE;
			i.y = (pos.y + MAP_Y_OFFSET) * MAP_SCALE;

			if (map.y < 0 || map.y >= cub->map->map_size.y
				|| map.x < 0 || map.x >= cub->map->map_size.x)
				continue ;
			draw_obj(cub, map, i, start);
			pos.x++;
		}
		pos.y++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Sort the sprites in order of distance so that if you look at one 
 * sprite through the over it will only show the sprite closest to you.
 * @param cub 
 */
static void	sort_sprites(t_cub *cub)
{
	int			i;
	int			j;

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
				swap_sprites(&(cub->sprite[i]), &(cub->sprite[j]));
			++j;
		}
		++i;
	}
}

int	draw_cub(t_cub *cub, t_ray *ray)
{
	int	x;

	x = 0;
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
