#include "cub3d.h"

/**
 * @brief Update the frames if you have gone through the game loop 5 times.
 * This helps with the movement of the frames.
 * @param cub 
 */
static inline void	update_frames(t_cub *cub)
{
	int	i;

	i = 0;
	cub->frame_counter++;
	if (cub->frame_counter >= 5)
	{
		cub->frame_counter = 0;
		while (i < SPRITE_COUNT)
		{
			cub->sprite[i].current_frame = (cub->sprite[i].current_frame + 1)
				% cub->sprite[i].text_count;
			cub->sprite[i].text_id = cub->sprite[i].current_frame;
			i++;
		}
	}
}

/**
 * @brief This is the game loop, in order for the sprites to be animated, it
 * checks if the game has gone through the loop 5 times and then it changes the
 * texture (to get the next frame of the animation).
 * @param cub
 */
int	update_game(t_cub *cub)
{
	update_frames(cub);
	draw_back(cub, &(cub->ray));
	if (cub->press->w)
		forward(cub);
	if (cub->press->a)
		left(cub);
	if (cub->press->s)
		back(cub);
	if (cub->press->d)
		right(cub);
	if (cub->press->rl)
		rot_left(cub, 1.0);
	if (cub->press->rr)
		rot_right(cub, 1.0);
	if (draw_cub(cub, cub->ray) == EXIT_FAILURE)
		return (ft_close(cub), 1);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}

/* WITHOUT BONUSES
int	update_game(t_cub *cub)
{
	draw_back(cub, &(cub->ray));
	if (cub->press->w)
		forward(cub);
	if (cub->press->a)
		left(cub);
	if (cub->press->s)
		back(cub);
	if (cub->press->d)
		right(cub);
	if (cub->press->rl)
		rot_left(cub, 1.0);
	if (cub->press->rr)
		rot_right(cub, 1.0);
	if (draw_cub(cub, cub->ray) == EXIT_FAILURE)
		return (ft_close(cub), 1);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}
*/
