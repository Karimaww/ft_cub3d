/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:21 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/23 16:09:17 by ksadykov         ###   ########.fr       */
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
		return (free_frames(file_names, sprite->text_count),
			printf("Error\nMalloc of sprite's textures.\n"), EXIT_FAILURE);
	while (i < sprite->text_count)
	{
		path = ft_strjoin(dir_name, file_names[i]);
		if (!path)
			return (free_frames(file_names, sprite->text_count),
				free(sprite->text),
				printf("Error\nNo such file in texture's dir.\n"), EXIT_FAILURE);
		if (sprite_text(cub, path, &(sprite->text[i])) == EXIT_FAILURE)
			return (free_frames(file_names, sprite->text_count), free(path),
				free(sprite->text), printf("Error\n"), EXIT_FAILURE);
		free(file_names[i]);
		free(path);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_frames(char **frames, int *i)
{
	*i = -1;
	frames[0] = ft_strdup("frames_book/");
	if (!frames[0])
		return (EXIT_FAILURE);
	frames[1] = ft_strdup("frames_green2/");
	if (!frames[1])
		return (free(frames[0]), EXIT_FAILURE);
	frames[2] = ft_strdup("frames_purple2/");
	if (!frames[2])
		return (free(frames[0]), free(frames[1]), EXIT_FAILURE);
	frames[3] = ft_strdup("frames_red2/");
	if (!frames[3])
		return (free(frames[0]), free(frames[1]), free(frames[2]),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_sprite(t_cub **cub)
{
	int		i;
	char	**frames;

	frames = malloc(sizeof(char *) * SPRITE_COUNT);
	if (!frames)
		return (EXIT_FAILURE);
	if (init_frames(frames, &i) == EXIT_FAILURE)
		return (free(frames), EXIT_FAILURE);
	(*cub)->sprite = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	if (!(*cub)->sprite)
		return (free_frames(frames, SPRITE_COUNT),
			printf("Error\nMalloc of t_sprite.\n"), EXIT_FAILURE);
	while (++i < SPRITE_COUNT)
	{
		(*cub)->sprite[i].text_count = 0;
		(*cub)->sprite[i].current_frame = 0;
		(*cub)->sprite[i].text_id = 0;
		find_position(*cub, &((*cub)->sprite[i]), i);
		(*cub)->sprite[i].initial_pos.x = (*cub)->sprite[i].pos.x;
		(*cub)->sprite[i].initial_pos.y = (*cub)->sprite[i].pos.y;
		if (iter_dir(cub, &((*cub)->sprite[i]), frames[i]) == EXIT_FAILURE)
			return (free_frames(frames, SPRITE_COUNT), free(frames), 1);
		(*cub)->num_frames++;
	}
	return (free_frames(frames, SPRITE_COUNT), free(frames), EXIT_SUCCESS);
}
