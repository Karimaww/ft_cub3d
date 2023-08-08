#include "cub3d.h"

void	hook_move(t_cub *cub, int key)
{
	if (key == A)
		cub->pos->x -= 0.1;
	if (key == W)
		cub->pos->y += 0.1;
	if (key == S)
		cub->pos->y -= 0.1;
	if (key == D)
		cub->pos->x += 0.1;
}

// void	hook_zoom(t_cub *cub, int keycode)
// {
// 	if (keycode == ARROW_UP)
// 		cub->view.zoom += 0.25;
// 	if (keycode == ARROW_DOWN && cub->view.zoom - 0.25 > 0)
// 		cub->view.zoom -= 0.25;
// }

// void	hook_rot(t_cub *cub, int keycode)
// {
// 	if (keycode == ARROW_LEFT)
// 		cub->view.alpha -= PI / 36;
// 	if (keycode == ARROW_RIGHT && cub->view.zoom - 0.25 > 0)
// 		cub->view.alpha += PI / 36;
// 	if (keycode == R)
// 		cub->view.theta += PI / 36;
// 	if (keycode == T)
// 		cub->view.theta -= PI / 36;
// }

// void	hook_up_down(t_cub *cub, int keycode)
// {
// 	if (keycode == UP)
// 		cub->view.up_down -= 1;
// 	if (keycode == DOWN)
// 		cub->view.up_down += 1;
// }

// void	hook_left_right(t_cub *cub, int keycode)
// {
// 	if (keycode == LEFT)
// 		cub->view.left_right -= 1;
// 	if (keycode == RIGHT)
// 		cub->view.left_right += 1;
// }

// void	hook_height(t_cub *cub, int keycode)
// {
// 	if (keycode == HUP)
// 		cub->view.h -= 0.1;
// 	if (keycode == HDOWN)
// 		cub->view.h += 0.1;
// }