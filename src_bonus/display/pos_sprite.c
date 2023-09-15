/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:27 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:27 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	compare(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

/**
 * @brief Function that gets all the file names from the designated directory
 * 
 * @param cub dir_name
 * @return int 
 */
int	iter_dir(t_cub **cub, t_sprite *sprite, char *dir_name)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*file_names[1000];

	sprite->text_count = 0;
	directory = opendir(dir_name);
	if (directory == NULL)
		return (printf("Error\nCannot open the directory.\n"), EXIT_FAILURE);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			file_names[sprite->text_count] = strdup(entry->d_name);
			sprite->text_count++;
		}
		entry = readdir(directory);
	}
	closedir(directory);
	qsort(file_names, sprite->text_count, sizeof(char *), compare);
	return (init_sprite_text(cub, sprite, dir_name, file_names));
}

void	check_sprite_dist(t_cub *cub, t_sprite *sprite, int v, int *collision)
{
	double	dx;
	double	dy;
	double	distance;
	int		i;

	*collision = 0;
	i = 0;
	while (i < v)
	{
		if (sprite != &(cub->sprite[i]))
		{
			dx = sprite->pos.x - cub->sprite[i].pos.x;
			dy = sprite->pos.y - cub->sprite[i].pos.y;
			distance = sqrt(dx * dx + dy * dy);
			if (distance < 0.1)
			{
				*collision = 1;
				break ;
			}
		}
		i++;
	}
}

/**
 * @brief Find a valid position for our sprites. It aims to not put the sprites
 * in walls or outside of the map and to not put them all together.
 * @param cub 
 * @param sprite 
 * @param v 
 */
void	find_position(t_cub *cub, t_sprite *sprite, int v)
{
	int	valid_position;
	int	collision;

	valid_position = 0;
	while (!valid_position)
	{
		sprite->pos.x = (double)rand() / RAND_MAX * (cub->map->map_size.x - 1);
		sprite->pos.y = (double)rand() / RAND_MAX * (cub->map->map_size.y - 1);
		if (sprite->pos.x < 0 || sprite->pos.x >= cub->map->map_size.x
			|| sprite->pos.y < 0 || sprite->pos.y >= cub->map->map_size.y)
			continue ;
		if (cub->map->map[(int)sprite->pos.y][(int)sprite->pos.x] == '1' ||
			cub->map->map[(int)sprite->pos.y][(int)sprite->pos.x] == ' ' ||
			cub->map->map[(int)sprite->pos.y][(int)sprite->pos.x] == '2')
			continue ;
		check_sprite_dist(cub, sprite, v, &collision);
		if (collision)
			continue ;
		valid_position = 1;
	}
}
