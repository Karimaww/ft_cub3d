#include "cub3d.h"


static void	texture_on_img(t_mlx *texture, t_ray *ray, t_cub **cub,
	int x, int y, int tex_x, int tex_y)
{
	// int	scale;

	// scale = y * texture->linel
	// 	- ((*cub)->mlx.win_size.y * ray->camera_x) * texture->linel
	// 	/ 2 + ray->line_h * texture->linel / 2;
	// tex_y = ((scale * texture->win_size.y) / ray->line_h)
	// 	/ texture->linel;
	// scale = line->y * texture->line_length
	// 	- (WIN_HEIGHT * root->game->player->cam_height) * texture->line_length
	// 	/ 2 + ray->line_height * texture->line_length / 2;
	// line->tex_y = ((scale * texture->height) / ray->line_height)
	// 	/ texture->line_length;
	// printf("TEX_Y : %d\n", tex_y);
	(void)ray;
	// printf("(*cub)->mlx.bpp : %d texture->bpp : %d\n", (*cub)->mlx.bpp, texture->bpp);
	(*cub)->mlx.addr[y * (*cub)->mlx.linel + x * (*cub)->mlx.bpp / 8] = 
		texture->addr[(int)(tex_y * texture->linel + (double)tex_x * ((double)texture->bpp / 8))];
	(*cub)->mlx.addr[y * (*cub)->mlx.linel + x * ((*cub)->mlx.bpp / 8) + 1] = 
		texture->addr[(int)(tex_y * texture->linel + (double)tex_x * ((double)texture->bpp / 8) + 1)];
	(*cub)->mlx.addr[y * (*cub)->mlx.linel + x * ((*cub)->mlx.bpp / 8) + 2] = 
		texture->addr[(int)(tex_y * texture->linel + (double)tex_x * ((double)texture->bpp / 8) + 2)];
}

void	pixel_on_img(int rgb, int x, int y, t_mlx *img)
{
	int	r;
	int	g;
	int	b;

	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	img->addr[y * img->linel + x * img->bpp / 8] = b;
	img->addr[y * img->linel + x * img->bpp / 8 + 1] = g;
	img->addr[y * img->linel + x * img->bpp / 8 + 2] = r;
}

int	get_texture_color(t_mlx *mlx, int texX, int texY)
{
	// Ensure that texX and texY are within the valid texture coordinates
	if (texX < 0)
		texX = 0;
	if (texY < 0)
		texY = 0;
	if (texX >= mlx->win_size.x)
		texX = mlx->win_size.x - 1;
	if (texY >= mlx->win_size.y)
		texY = mlx->win_size.y - 1;

	// Calculate the pixel index in the texture data array
	int pixel_index = texY * mlx->win_size.y + texX;

	// Retrieve the color value from the texture data array
	unsigned int color = mlx->addr[pixel_index];

	return (int)color; // Return the color as an integer
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
		texture_on_img(&side, *ray, &cub, x, y, tex_x, tex_y);
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
