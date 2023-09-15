/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:21 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:21 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	init_sprite_text(t_cub **cub, t_sprite *sprite,
					char *dir_name, char **file_names)
{
	char	*path;
	int		i;

	i = 0;
	sprite->text = malloc(sizeof(t_sprite) * (sprite->text_count));
	if (!sprite->text)
		return (free_frames(file_names, 1000),
			printf("Error\nMalloc of sprite's textures.\n"), EXIT_FAILURE);
	while (i < sprite->text_count)
	{
		path = ft_strjoin(dir_name, file_names[i]);
		if (!path)
			return (free_frames(file_names, 1000),
				printf("Error\nNo such file in texture's dir.\n"), EXIT_FAILURE);
		sprite_text(cub, path, &(sprite->text[i]));
		free(file_names[i]);
		free(path);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_frames(char **frames)
{
	frames[0] = ft_strdup("frames_book/");
	frames[1] = ft_strdup("frames_green2/");
	frames[2] = ft_strdup("frames_purple2/");
	frames[3] = ft_strdup("frames_red2/");
}

int	init_sprite(t_cub **cub)
{
	int		i;
	char	**frames;

	frames = malloc(sizeof(char *) * SPRITE_COUNT);
	if (!frames)
		return (EXIT_FAILURE);
	init_frames(frames);
	i = 0;
	(*cub)->sprite = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	if (!(*cub)->sprite)
		return (free_frames(frames, SPRITE_COUNT),
			printf("Error\nMalloc of t_sprite.\n"), EXIT_FAILURE);
	while (i < SPRITE_COUNT)
	{
		(*cub)->sprite[i].text_count = 0;
		(*cub)->sprite[i].current_frame = 0;
		(*cub)->sprite[i].text_id = 0;
		find_position(*cub, &((*cub)->sprite[i]), i);
		(*cub)->sprite[i].initial_pos.x = (*cub)->sprite[i].pos.x;
		(*cub)->sprite[i].initial_pos.y = (*cub)->sprite[i].pos.y;
		if (iter_dir(cub, &((*cub)->sprite[i]), frames[i]) == EXIT_FAILURE)
			return (free_frames(frames, SPRITE_COUNT), EXIT_FAILURE);
		i++;
	}
	return (free_frames(frames, SPRITE_COUNT), EXIT_SUCCESS);
}
