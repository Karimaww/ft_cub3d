#include "cub3d.h"

void	get_size_sprite(t_cub **cub, t_sprite *sprite)
{
	//calculate height of the sprite on screen
	sprite->h = abs((int)(((*cub)->mlx.win_size.y
				/ sprite->transform.y))) / VDIV;
	//calculate lowest and highest pixel to fill in current stripe
	sprite->draw_start.y = - sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2
		+ sprite->v_move;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2
		+ sprite->v_move;
	if (sprite->draw_end.y >= (*cub)->mlx.win_size.y)
		sprite->draw_end.y = (*cub)->mlx.win_size.y - 1;

	//calculate width of the sprite
	sprite->w = abs((int)(((*cub)->mlx.win_size.y
					/ sprite->transform.y))) / UDIV;
	sprite->draw_start.x = -sprite->w / 2
		+ sprite->screen_x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->w / 2
		+ sprite->screen_x;
	if (sprite->draw_end.x >= (*cub)->mlx.win_size.x)
		sprite->draw_end.x = (*cub)->mlx.win_size.x - 1;
}

void	draw_obj(t_cub **cub, t_sprite *sprite)
{
	int		stripe;
	int		y;
	t_vec2	tex;
	int		d;
	int		i;

	i = 0;
	stripe = sprite->draw_start.x;
	while (stripe < sprite->draw_end.x)
	{
		tex.x = (int)(256 * (stripe - (-sprite->w / 2
						+ sprite->screen_x))
				* sprite->text[sprite->text_id].win_size.x
				/ sprite->w) / 256;
		y = sprite->draw_start.y;
		if (sprite->transform.y > 0 && stripe > 0
			&& stripe < (*cub)->mlx.win_size.x
			&& sprite->transform.y < (*cub)->z_buf[stripe])
		{
			while (y < sprite->draw_end.y)
			{
				d = (y - sprite->v_move) * 256
					- (*cub)->mlx.win_size.y * 128
					+ sprite->h * 128;
				tex.y = ((d * sprite->text[sprite->text_id].win_size.y)
						/ sprite->h / 256);
				texture_on_img(&(sprite->text[sprite->text_id]), cub, stripe,
					y, tex.x, tex.y);
				y++;
			}
		}
		stripe++;
	}
}

void	draw_sprite(t_cub **cub, t_ray *ray, t_sprite *sprite)
{
	//translate sprite position to relative to camera
	sprite->pos.x = (int)(sprite->initial_pos.x) + 0.25;
	sprite->pos.y = (int)(sprite->initial_pos.y) + 0.25;
	sprite->pos.x -= ray->pos.x;
	sprite->pos.y -= ray->pos.y;

	sprite->inv_det = 1.0 / (ray->plane.x * ray->dir.y
			- ray->plane.y * ray->dir.x);
	sprite->transform.x = sprite->inv_det
		* (ray->dir.y * sprite->pos.x
			- ray->dir.x * sprite->pos.y);
	//this is actually the depth inside the screen, that what Z is in 3D
	sprite->transform.y = sprite->inv_det
		* (-ray->plane.y * sprite->pos.x
			+ ray->plane.x * sprite->pos.y);
	sprite->screen_x = (int)((*cub)->mlx.win_size.x / 2
			* (1 + sprite->transform.x / sprite->transform.y));
	sprite->v_move = (int)(VMOVE / sprite->transform.y);
	get_size_sprite(cub, sprite);
	draw_obj(cub, sprite);
}


