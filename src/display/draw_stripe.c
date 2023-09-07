#include "cub3d.h"

void	texture_on_img(t_mlx *texture, t_cub **cub,
	int x, int y, int tex_x, int tex_y)
{
	int	r;
	int	g;
	int	b;
	// printf("x : %d\n", x);
	// printf("y : %d\n", y);
	// printf("tex_x : %d\n", tex_x);
	// printf("tex_y : %d\n", tex_y);
	// printf("values : x : %d y : %d tex_x : %d tex_y : %d\n", x, y, tex_x, tex_y);
	if (!((tex_y >= 0 && tex_y < texture->win_size.y
		&& tex_x >= 0 && tex_x < texture->win_size.x)))
		return ;
	r = texture->addr[(int)(tex_y * texture->linel + (double)tex_x * ((double)texture->bpp / 8))]; 
	g = texture->addr[(int)(tex_y * texture->linel + (double)tex_x * ((double)texture->bpp / 8) + 1)];
	b = texture->addr[(int)(tex_y * texture->linel + (double)tex_x * ((double)texture->bpp / 8) + 2)];
	if (r == 0 && g == 0 && b == 0)
		return ;
	(*cub)->mlx.addr[y * (*cub)->mlx.linel
		+ x * (*cub)->mlx.bpp / 8]
		= r;
	(*cub)->mlx.addr[y * (*cub)->mlx.linel
		+ x * ((*cub)->mlx.bpp / 8) + 1]
		= g;
	(*cub)->mlx.addr[y * (*cub)->mlx.linel
		+ x * ((*cub)->mlx.bpp / 8) + 2]
		= b;
}

void	draw_side(t_mlx side, t_ray **ray, t_cub *cub, int x)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	if ((*ray)->side == 0)
		wall_x = (*ray)->pos.y + (*ray)->perp_dist * (*ray)->ray_dir.y;
	else
		wall_x = (*ray)->pos.x + (*ray)->perp_dist * (*ray)->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(side.win_size.x));
	if ((*ray)->side == 0 && (*ray)->ray_dir.x > 0)
		tex_x = side.win_size.x - tex_x - 1;
	if ((*ray)->side == 1 && (*ray)->ray_dir.y < 0)
		tex_x = side.win_size.x - tex_x - 1;
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * side.win_size.y / (*ray)->line_h;
	// Starting texture coordinate
	tex_pos = ((*ray)->draw_start - cub->mlx.win_size.y / 2
		+ (*ray)->line_h / 2) * step;
	for(int y = (*ray)->draw_start; y < (*ray)->draw_end; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		tex_y = (int)tex_pos & (side.win_size.y - 1);
		tex_pos += step;
		texture_on_img(&side, &cub, x, y, tex_x, tex_y);
	}
}

void	draw_stripe(t_ray **ray, t_cub *cub, int x)
{
	if ((*ray)->side == 1 && (*ray)->ray_dir.y > 0)
		draw_side(cub->north, ray, cub, x);
	else if ((*ray)->side == 1 && (*ray)->ray_dir.y <= 0)
		draw_side(cub->south, ray, cub, x);
	else if ((*ray)->side == 0 && (*ray)->ray_dir.x > 0)
		draw_side(cub->east, ray, cub, x);
	else
		draw_side(cub->west, ray, cub, x);
}
