#include "cub3d.h"

void	free_cub_params(t_cub *cub)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (cub->sprite)
	{
		while (j < SPRITE_COUNT)
		{
			i = 0;
			while (i < cub->sprite[j].text_count)
			{
				close_mlx(cub, cub->sprite[j].text[i]);
				i++;
			}
			if (cub->sprite[j].text)
				free(cub->sprite[j].text);
			j++;
		}
		free(cub->sprite);
	}
	if (cub->z_buf)
		free(cub->z_buf);
}

void	ft_close(t_cub *cub)
{
	if (cub->map)
		free_map(cub->map);
	close_mlx(cub, cub->north);
	close_mlx(cub, cub->south);
	close_mlx(cub, cub->east);
	close_mlx(cub, cub->west);
	close_mlx(cub, cub->door);
	if (cub->press)
		free(cub->press);
	if (cub->ray)
	{
		free(cub->ray);
		cub->ray = NULL;
	}
	free_cub_params(cub);
	mlx_do_key_autorepeaton(cub->mlx.mlx);
	close_mlx(cub, cub->mlx);
	if (cub)
		free(cub);
	exit(0);
}

void	do_move(int key, t_cub *cub)
{
	if (key == W || cub->press->w == 1)
		cub->press->w = 1;
	if (key == A || cub->press->a == 1)
		cub->press->a = 1;
	if (key == S || cub->press->s == 1)
		cub->press->s = 1;
	if (key == D || cub->press->d == 1)
		cub->press->d = 1;
	if (key == RL || cub->press->rl == 1)
		cub->press->rl = 1;
	if (key == RR || cub->press->rr == 1)
		cub->press->rr = 1;
}

int	ft_key_choose(int key, t_cub *cub)
{
	if (key == ESC)
		ft_close(cub);
	do_move(key, cub);
	if (key == SPC)
		open_door(cub);
	return (0);
}

int	mouse_hook(t_cub *cub)
{
	ft_close(cub);
	return (0);
}

/*without bonus
int	ft_key_choose(int key, t_cub *cub)
{
	if (key == ESC)
		ft_close(cub);
	do_move(key, cub);
	return (0);
}
*/
