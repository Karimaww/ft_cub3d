#include "cub3d.h"

void	get_size_sprite(t_cub **cub)
{
	//calculate height of the sprite on screen
	(*cub)->sprite->h = abs((int)((*cub)->mlx.win_size.y
			/ (*cub)->sprite->transform.y));
	//calculate lowest and highest pixel to fill in current stripe
	(*cub)->sprite->draw_start.y = - (*cub)->sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2;
	if ((*cub)->sprite->draw_start.y < 0)
		(*cub)->sprite->draw_start.y = 0;
	(*cub)->sprite->draw_end.y = (*cub)->sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2;
	if ((*cub)->sprite->draw_end.y >= (*cub)->mlx.win_size.y)
		(*cub)->sprite->draw_end.y = (*cub)->mlx.win_size.y - 1;

	//calculate width of the sprite
	(*cub)->sprite->w = abs((int)((*cub)->mlx.win_size.y
				/ (*cub)->sprite->transform.y));
	(*cub)->sprite->draw_start.x = -(*cub)->sprite->w / 2
		+ (*cub)->sprite->screen_x;
	if ((*cub)->sprite->draw_start.x < 0)
		(*cub)->sprite->draw_start.x = 0;
	(*cub)->sprite->draw_end.x = (*cub)->sprite->w / 2
		+ (*cub)->sprite->screen_x;
	if ((*cub)->sprite->draw_end.x >= (*cub)->mlx.win_size.x)
		(*cub)->sprite->draw_end.x = (*cub)->mlx.win_size.x - 1;
}

void	draw_obj(t_cub **cub)
{
	int		stripe;
	int		y;
	t_vec2	tex;
	int		d;

	stripe = (*cub)->sprite->draw_start.x;
	while (stripe < (*cub)->sprite->draw_end.x)
	{
		tex.x = (int)(256 * (stripe - (-(*cub)->sprite->w / 2
						+ (*cub)->sprite->screen_x))
				* (*cub)->sprite->text.win_size.x
				/ (*cub)->sprite->w) / 256;
		y = (*cub)->sprite->draw_start.y;
		while (y < (*cub)->sprite->draw_end.y)
		{
			d = y * 256 - (*cub)->mlx.win_size.y
				+ (*cub)->sprite->text.win_size.y * 128;
			tex.y = ((d * (*cub)->sprite->text.win_size.y)
					/ (*cub)->sprite->h / 256);
			texture_on_img(&((*cub)->sprite->text), cub, stripe,
				y, tex.x, tex.y);
			y++;
		}
		stripe++;
	}
}

void	draw_sprite(t_cub **cub, t_ray *ray)
{
	//translate sprite position to relative to camera
	(*cub)->sprite->pos.x -= ray->pos.x;
	(*cub)->sprite->pos.y -= ray->pos.y;

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
	get_size_sprite(cub);
	draw_obj(cub);
}

