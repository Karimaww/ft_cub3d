#include "cub3d.h"

void	draw_stripe(t_ray **ray, t_cub *cub, int x)
{
	//draw the pixels of the stripe as a vertical line
	for(int y = (*ray)->draw_start; y < (*ray)->draw_end; y++)
	{
		int color;
		color = get_color(ray, cub);
		if ((*ray)->side == 1)
			color = (color >> 1) & 8355711;
		pixel_put(&(cub->mlx), x, y, color);
	}
	//texturing calculations
	// int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

	// //calculate value of wallX
	// double wallX; //where exactly the wall was hit
	// if (side == 0) wallX = posY + perpWallDist * rayDirY;
	// else           wallX = posX + perpWallDist * rayDirX;
	// wallX -= floor((wallX));

	// //x coordinate on the texture
	// int texX = int(wallX * double(texWidth));
	// if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
	// if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
	// // How much to increase the texture coordinate per screen pixel
	// double step = 1.0 * texHeight / lineHeight;
	// // Starting texture coordinate
	// double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
	// for(int y = drawStart; y<drawEnd; y++)
	// {
	// // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
	// int texY = (int)texPos & (texHeight - 1);
	// texPos += step;
	// Uint32 color = texture[texNum][texHeight * texY + texX];
	// //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	// if(side == 1) color = (color >> 1) & 8355711;
	// buffer[y][x] = color;
	// }
}