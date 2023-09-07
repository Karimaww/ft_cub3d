#include "cub3d.h"

int	compare(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

int	sprite_text(t_cub **cub, char *file_name, t_mlx *text)
{
	text->win = NULL;
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
	(*cub)->sprite->text = malloc(sizeof(t_sprite) * (sprite->text_count));
	for (int i = 0; i < sprite->text_count; i++)
	{
		path = ft_strjoin(dir_name, file_names[i]); 
		if (!path)
			return (EXIT_FAILURE);
		sprite_text(cub, path, &((*cub)->sprite->text[i]));
		(*cub)->sprite->text[i].i = i;
		// printf("file : %s\n", file_names[i]);
		free(file_names[i]);
		free(path);
	}
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
	if (iter_dir(cub, (*cub)->sprite, "frames/") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
