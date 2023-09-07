#include "cub3d.h"

void	get_size_sprite(t_cub **cub)
{
	//calculate height of the sprite on screen
	(*cub)->sprite->h = abs((int)(((*cub)->mlx.win_size.y
				/ (*cub)->sprite->transform.y))) / VDIV;
	//calculate lowest and highest pixel to fill in current stripe
	(*cub)->sprite->draw_start.y = - (*cub)->sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2
		+ (*cub)->sprite->v_move;
	if ((*cub)->sprite->draw_start.y < 0)
		(*cub)->sprite->draw_start.y = 0;
	(*cub)->sprite->draw_end.y = (*cub)->sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2
		+ (*cub)->sprite->v_move;
	if ((*cub)->sprite->draw_end.y >= (*cub)->mlx.win_size.y)
		(*cub)->sprite->draw_end.y = (*cub)->mlx.win_size.y - 1;

	//calculate width of the sprite
	(*cub)->sprite->w = abs((int)(((*cub)->mlx.win_size.y
					/ (*cub)->sprite->transform.y))) / UDIV;
	(*cub)->sprite->draw_start.x = -(*cub)->sprite->w / 2
		+ (*cub)->sprite->screen_x;
	if ((*cub)->sprite->draw_start.x < 0)
		(*cub)->sprite->draw_start.x = 0;
	(*cub)->sprite->draw_end.x = (*cub)->sprite->w / 2
		+ (*cub)->sprite->screen_x;
	if ((*cub)->sprite->draw_end.x >= (*cub)->mlx.win_size.x)
		(*cub)->sprite->draw_end.x = (*cub)->mlx.win_size.x - 1;
}

// void	delay(int microseconds)
// {
//     struct timeval start_time, current_time;
//     gettimeofday(&start_time, NULL);

//     while (1) {
//         gettimeofday(&current_time, NULL);
//         int elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000000 + (current_time.tv_usec - start_time.tv_usec);
        
//         if (elapsed_time >= microseconds) {
//             break;
//         }
//     }
// }

void	draw_obj(t_cub **cub)
{
	int		stripe;
	int		y;
	t_vec2	tex;
	int		d;
	int		i;

	i = 0;
	printf("text id : %d\n", (*cub)->sprite_text_id);
	stripe = (*cub)->sprite->draw_start.x;
	// while (i < (*cub)->sprite->text_count)
	// {
		// printf("frame mlx : %d\n", (*cub)->sprite->text[i].i);
		while (stripe < (*cub)->sprite->draw_end.x)
		{
			tex.x = (int)(256 * (stripe - (-(*cub)->sprite->w / 2
							+ (*cub)->sprite->screen_x))
					* (*cub)->sprite->text[(*cub)->sprite_text_id].win_size.x
					/ (*cub)->sprite->w) / 256;
			y = (*cub)->sprite->draw_start.y;
			if ((*cub)->sprite->transform.y > 0 && stripe > 0
				&& stripe < (*cub)->mlx.win_size.x
				&& (*cub)->sprite->transform.y < (*cub)->sprite->z_buf[stripe])
			{
				while (y < (*cub)->sprite->draw_end.y)
				{
					d = (y - (*cub)->sprite->v_move) * 256
						- (*cub)->mlx.win_size.y * 128
						+ (*cub)->sprite->h * 128;
					tex.y = ((d * (*cub)->sprite->text[(*cub)->sprite_text_id].win_size.y)
							/ (*cub)->sprite->h / 256);
					texture_on_img(&((*cub)->sprite->text[(*cub)->sprite_text_id]), cub, stripe,
						y, tex.x, tex.y);
					y++;
				}
			}
			stripe++;
		}

	// 	delay(20000);

	// 	i++;
	// }
}

void	draw_sprite(t_cub **cub, t_ray *ray)
{
	//translate sprite position to relative to camera
	(*cub)->sprite->pos.x = 2.5;
	(*cub)->sprite->pos.y = 2.5;
	(*cub)->sprite->pos.x -= ray->pos.x;
	(*cub)->sprite->pos.y -= ray->pos.y;
	// (*cub)->sprite->pos.x -= (*cub)->map->player.x;
	// (*cub)->sprite->pos.y -= (*cub)->map->player.y;

	(*cub)->sprite->inv_det = 1.0 / (ray->plane.x * ray->dir.y
			- ray->plane.y * ray->dir.x);
	(*cub)->sprite->transform.x = (*cub)->sprite->inv_det
		* (ray->dir.y * (*cub)->sprite->pos.x
			- ray->dir.x * (*cub)->sprite->pos.y);
	//this is actually the depth inside the screen, that what Z is in 3D
	(*cub)->sprite->transform.y = (*cub)->sprite->inv_det
		* (-ray->plane.y * (*cub)->sprite->pos.x
			+ ray->plane.x * (*cub)->sprite->pos.y);
	(*cub)->sprite->screen_x = (int)((*cub)->mlx.win_size.x / 2
			* (1 + (*cub)->sprite->transform.x / (*cub)->sprite->transform.y));
	(*cub)->sprite->v_move = (int)(VMOVE / (*cub)->sprite->transform.y);
	get_size_sprite(cub);
	draw_obj(cub);
}


