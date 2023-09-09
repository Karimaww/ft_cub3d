#include "cub3d.h"

// int	find_door(t_cub *cub, int x, int y)
// {
// 	t_door	*door;

// 	door = cub->map->lst_doors;
// 	while (door)
// 	{
// 		//la porte correspond a la position et elle est ouverte
// 		if (door->pos.x == x && door->pos.y == y && door->open == 1)
// 			return (1);
// 		door = door->next;
// 	}
// 	// la porte est fermee
// 	return (0);
// }

// /**
//  * @brief Below are some functions to deal with hooks it checks if there is a
//  * door and if the door is open or if a wall was found.
//  * @param cub
//  */
// void	forward(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(cub->ray->pos.x + cub->ray->dir.x * SPEED);
// 	y = (int)(cub->ray->pos.y);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| (cub->map->map[x][y] != '1' && cub->map->map[x][y] != '2'))
// 		cub->ray->pos.x += cub->ray->dir.x * SPEED;
// 	x = (int)(cub->ray->pos.x);
// 	y = (int)(cub->ray->pos.y + cub->ray->dir.y * SPEED);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 	|| (cub->map->map[x][y] != '1' && cub->map->map[x][y] != '2'))
// 		cub->ray->pos.y += cub->ray->dir.y * SPEED;
// }

// void	back(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(cub->ray->pos.x - cub->ray->dir.x * SPEED);
// 	y = (int)(cub->ray->pos.y);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| cub->map->map[x][y] != '1')
// 		cub->ray->pos.x -= cub->ray->dir.x * SPEED;
// 	x = (int)(cub->ray->pos.x);
// 	y = (int)(cub->ray->pos.y - cub->ray->dir.y * SPEED);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| cub->map->map[x][y] != '1')
// 		cub->ray->pos.y -= cub->ray->dir.y * SPEED;
// }

// void	left(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(cub->ray->pos.x - cub->ray->plane.x * SPEED);
// 	y = (int)(cub->ray->pos.y);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| (cub->map->map[x][y] != '1' && cub->map->map[x][y] != '2'))
// 		cub->ray->pos.x -= cub->ray->plane.x * SPEED;
// 	x = (int)(cub->ray->pos.x);
// 	y = (int)(cub->ray->pos.y - cub->ray->plane.y * SPEED);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| (cub->map->map[x][y] != '1' && cub->map->map[x][y] != '2'))
// 		cub->ray->pos.y -= cub->ray->plane.y * SPEED;
// }

// void	right(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(cub->ray->pos.x + cub->ray->plane.x * SPEED);
// 	y = (int)(cub->ray->pos.y);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| (cub->map->map[x][y] != '1' && cub->map->map[x][y] != '2'))
// 		cub->ray->pos.x += cub->ray->plane.x * SPEED;
// 	x = (int)(cub->ray->pos.x);
// 	y = (int)(cub->ray->pos.y + cub->ray->plane.y * SPEED);
// 	if ((cub->map->map[x][y] == '2' && find_door(cub, x, y))
// 		|| (cub->map->map[x][y] != '1' && cub->map->map[x][y] != '2'))
// 		cub->ray->pos.y += cub->ray->plane.y * SPEED;
// }
// returns 1 if all boundries are ok
int	verif_boundries(t_cub *cub, int x, int y)
{
	if (x < 0 || y < 0
		|| y >= cub->map->map_size.x
		|| x >= cub->map->map_size.y)
		return (0);
	return (1);
}
/**
 * @brief Below are some functions to deal with hooks it checks if there is a
 * door and if the door is open or if a wall was found.
 * @param cub
 */
void	forward(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x + cub->ray->dir.x * SPEED + OFFSET);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.x += cub->ray->dir.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y + cub->ray->dir.y * SPEED + OFFSET);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.y += cub->ray->dir.y * SPEED;
}

void	back(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x - cub->ray->dir.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.x -= cub->ray->dir.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y - cub->ray->dir.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.y -= cub->ray->dir.y * SPEED;
}

void	left(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x - cub->ray->plane.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.x -= cub->ray->plane.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y - cub->ray->plane.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.y -= cub->ray->plane.y * SPEED;
}

void	right(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->ray->pos.x + cub->ray->plane.x * SPEED);
	y = (int)(cub->ray->pos.y);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.x += cub->ray->plane.x * SPEED;
	x = (int)(cub->ray->pos.x);
	y = (int)(cub->ray->pos.y + cub->ray->plane.y * SPEED);
	if (verif_boundries(cub, x, y) && cub->map->map[x][y] != '2'
		&& cub->map->map[x][y] != '1')
		cub->ray->pos.y += cub->ray->plane.y * SPEED;
}

void	open_door(t_cub *cub)
{
	// t_door	*door;

	// door = cub->map->lst_doors;
	// while (door)
	// {
	// 	if (door->pos.x == cub->ray->map.x && door->pos.y == cub->ray->map.y)
	// 	{
	// 		if (door->open == 1)
	// 		{
	// 			//printf("here in open_door\n");
	// 			door->open = 0;
	// 			// return ;
	// 		}
	// 		else
	// 			door->open = 1;
	// 		// return ;
	// 	}
	// 	door = door->next;
	// }
	int	x;
	int	y;

	// x = cub->ray->map.x;
	// y = cub->ray->map.y;
	// x = (int)(cub->ray->pos.x + cub->ray->dir.x);
	// y = (int)(cub->ray->pos.y + cub->ray->dir.y);
	x = (int)(cub->ray->pos.x + cub->ray->dir.x);
	y = (int)(cub->ray->pos.y + cub->ray->dir.y);
	if (x >= 0 && x < cub->map->map_size.x
		&& y >= 0 && y < cub->map->map_size.y
		&& cub->map->map[x][y] == '2')
		cub->map->map[x][y] = '3';
	else if (x >= 0 && x < cub->map->map_size.x
		&& y >= 0 && y < cub->map->map_size.y
		&& cub->map->map[x][y] == '3')
		cub->map->map[x][y] = '2';

	// if (cub->map->map[cub->ray->map.x][cub->ray->map.y] == '2')
	// 	cub->map->map[cub->ray->map.x][cub->ray->map.y] = '3';
	// else if (cub->map->map[cub->ray->map.x][cub->ray->map.y] == '3')
	// 	cub->map->map[cub->ray->map.x][cub->ray->map.y] = '2';
	return ;
}
