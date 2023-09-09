#include "cub3d.h"

static int	compare(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

int	sprite_text(t_cub **cub, char *file_name, t_mlx *text)
{
	text->win = NULL;
	text->mlx = NULL;
	text->img = mlx_xpm_file_to_image((*cub)->mlx.mlx,
			file_name, &(text->win_size.x),
			&(text->win_size.y));
	if (!text->img)
		return (EXIT_FAILURE);
	text->addr = mlx_get_data_addr(text->img,
			&(text->bpp),
			&(text->linel), &(text->endian));
	return (EXIT_SUCCESS);
}

static void	free_frames(char **frames, int size)
{
	int	i;

	i = 0;
	if (frames)
	{
		while (i < size)
		{
			if (frames[i])
				free(frames[i]);
			i++;
		}
		free(frames);
	}
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
	char			*path;

	sprite->text_count = 0;
	directory = opendir(dir_name);
	if (directory == NULL)
		return (perror("opendir"), EXIT_FAILURE);
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
	sprite->text = malloc(sizeof(t_sprite) * (sprite->text_count));
	if (!sprite->text)
		return (free_frames(file_names, 1000), EXIT_FAILURE);
	for (int i = 0; i < sprite->text_count; i++)
	{
		path = ft_strjoin(dir_name, file_names[i]); 
		if (!path)
			return (free_frames(file_names, 1000), EXIT_FAILURE);
		sprite_text(cub, path, &(sprite->text[i]));
		free(file_names[i]);
		free(path);
	}
	return (EXIT_SUCCESS);
}

static void	find_position(t_cub *cub, t_sprite *sprite, int v)
{
	int	valid_position;

	valid_position = 0;
	while (!valid_position)
	{
		sprite->pos.x = (double)rand() / RAND_MAX * (cub->map->map_size.x - 1);
		sprite->pos.y = (double)rand() / RAND_MAX * (cub->map->map_size.y - 1);
		if (sprite->pos.x < 0 || sprite->pos.x >= cub->map->map_size.x ||
			sprite->pos.y < 0 || sprite->pos.y >= cub->map->map_size.y)
			continue ;
		if (cub->map->map[(int)sprite->pos.y][(int)sprite->pos.x] == '1')
			continue ;
		int collision = 0;
		for (int i = 0; i < v; i++)
		{
			if (sprite != &(cub->sprite[i]))
			{
				double dx = sprite->pos.x - cub->sprite[i].pos.x;
				double dy = sprite->pos.y - cub->sprite[i].pos.y;
				double distance = sqrt(dx*dx + dy*dy);
				if (distance < 0.01)
				{
					collision = 1;
					break ;
				}
			}
		}
		if (collision)
		{
			continue;
		}
		valid_position = 1;
	}
}

int	init_sprite(t_cub **cub)
{
	int		i;
	char	**frames;

	frames = malloc(sizeof(char *) * SPRITE_COUNT);
	if (!frames)
		return (EXIT_FAILURE);
	frames[0] = ft_strdup("frames_book/");
	frames[1] = ft_strdup("frames_green2/");
	frames[2] = ft_strdup("frames_purple2/");
	frames[3] = ft_strdup("frames_red2/");
	i = 0;
	(*cub)->sprite = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	if (!(*cub)->sprite)
		return (free_frames(frames, SPRITE_COUNT), EXIT_FAILURE);
	while (i < SPRITE_COUNT)
	{
		(*cub)->sprite[i].text_count = 0;
		(*cub)->sprite[i].current_frame = 0;
		(*cub)->sprite->text_id = 0;
		find_position(*cub, &((*cub)->sprite[i]), i);
		(*cub)->sprite[i].initial_pos.x = (*cub)->sprite[i].pos.x;
		(*cub)->sprite[i].initial_pos.y = (*cub)->sprite[i].pos.y;
		if (iter_dir(cub, &((*cub)->sprite[i]), frames[i]) == EXIT_FAILURE)
			return (free_frames(frames, SPRITE_COUNT), EXIT_FAILURE);
		i++;
	}
	return (free_frames(frames, SPRITE_COUNT), EXIT_SUCCESS);
}
