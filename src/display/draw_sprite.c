#include "cub3d.h"

/**
 * @brief Get the size sprite object
 * h/w : height/width of the sprite
 * draw_start : calculate lowest and highest pixel to fill in current stripe
 * @param cub 
 * @param sprite 
 */
void	get_size_sprite(t_cub **cub, t_sprite *sprite)
{
	sprite->h = abs((int)(((*cub)->mlx.win_size.y / sprite->transform.y)))
		/ VDIV;
	sprite->draw_start.y = -sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2
		+ sprite->v_move;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->h / 2
		+ (*cub)->mlx.win_size.y / 2
		+ sprite->v_move;
	if (sprite->draw_end.y >= (*cub)->mlx.win_size.y)
		sprite->draw_end.y = (*cub)->mlx.win_size.y - 1;
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

/**
 * @brief y_d is a variable for the norme, otherwise y_d.x = d and y_d.y = y
 * st : stripe
 * sp : sprite
 * @param cub 
 * @param sprite 
 */
static void	draw_obj(t_cub **cub, t_sprite *sp)
{
	t_vec2	tex;
	int		d;
	t_vec2	val;

	val.x = sp->draw_start.x;
	while (val.x < sp->draw_end.x)
	{
		tex.x = (int)(256 * (val.x - (-sp->w / 2 + sp->screen_x))
				* sp->text[sp->text_id].win_size.x / sp->w) / 256;
		val.y = sp->draw_start.y;
		if (sp->transform.y > 0 && val.x > 0 && val.x < (*cub)->mlx.win_size.x
			&& sp->transform.y < (*cub)->z_buf[val.x])
		{
			while (val.y < sp->draw_end.y)
			{
				d = (val.y - sp->v_move) * 256
					- (*cub)->mlx.win_size.y * 128 + sp->h * 128;
				tex.y = ((d * sp->text[sp->text_id].win_size.y)
						/ sp->h / 256);
				texture_on_img(&(sp->text[sp->text_id]), cub, tex, val);
				(val.y)++;
			}
		}
		(val.x)++;
	}
}

void	draw_sprite(t_cub **cub, t_ray *ray, t_sprite *sprite)
{
	sprite->pos.x = (int)(sprite->initial_pos.x) + 0.25;
	sprite->pos.y = (int)(sprite->initial_pos.y) + 0.25;
	sprite->pos.x -= ray->pos.x;
	sprite->pos.y -= ray->pos.y;
	sprite->inv_det = 1.0 / (ray->plane.x * ray->dir.y
			- ray->plane.y * ray->dir.x);
	sprite->transform.x = sprite->inv_det
		* (ray->dir.y * sprite->pos.x
			- ray->dir.x * sprite->pos.y);
	sprite->transform.y = sprite->inv_det
		* (-ray->plane.y * sprite->pos.x
			+ ray->plane.x * sprite->pos.y);
	sprite->screen_x = (int)((*cub)->mlx.win_size.x / 2
			* (1 + sprite->transform.x / sprite->transform.y));
	sprite->v_move = (int)(VMOVE / sprite->transform.y);
	get_size_sprite(cub, sprite);
	draw_obj(cub, sprite);
}


