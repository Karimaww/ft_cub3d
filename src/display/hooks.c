#include "cub3d.h"

/*void Buttons(unsigned char key,int x,int y)
{
 if(key=='a'){ pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));}     
 if(key=='d'){ pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 
 if(key=='w'){ px+=pdx*5; py+=pdy*5;}
 if(key=='s'){ px-=pdx*5; py-=pdy*5;}
 glutPostRedisplay();
}*/

void	hook_up(t_cub **cub)
{
	// cub->ray->pos.x += ray->delta_dist.x * 5;
	// cub->ray->pos.y += ray->delta_dist.y * 5;
	printf("(*cub)->ray->pos.x : %d\n", (int)((*cub)->ray->pos.x));
	if((*cub)->map->map[(int)((*cub)->ray->pos.x + (*cub)->ray->dir.x * 0.5)][(int)((*cub)->ray->pos.y)] == '0')
	{
		printf("yuyu\n");
		(*cub)->ray->pos.x += (*cub)->ray->dir.x * 0.5;
		printf("zuzu\n");
	}
	if((*cub)->map->map[(int)((*cub)->ray->pos.x)][(int)((*cub)->ray->pos.y + (*cub)->ray->dir.y * 0.5)] == '0')
	{
		printf("yuyu 2\n");
		(*cub)->ray->pos.y += (*cub)->ray->dir.y * 0.5;
		printf("zuzu 2\n");
	}
}

void	hook_down(t_cub **cub)
{
	// cub->ray->pos.x -= ray->delta_dist.x * 5;
	// cub->ray->pos.y -= ray->delta_dist.y * 5;
	//if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
	if ((*cub)->map->map[(int)((*cub)->ray->pos.x - (*cub)->ray->dir.x * 0.5)][(int)((*cub)->ray->pos.y)] == '0')
		(*cub)->ray->pos.x -= (*cub)->ray->dir.x * 0.5;
	//if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
	if ((*cub)->map->map[(int)((*cub)->ray->pos.x)][(int)((*cub)->ray->pos.y - (*cub)->ray->dir.y * 0.5)] == '0')
		(*cub)->ray->pos.y -= (*cub)->ray->dir.y * 0.5;
}

// i dont know what to do :D
void	hook_left(t_cub **cub)
{
	double	old_dir;
	double	old_plane;

	old_dir = (*cub)->ray->dir.x;
	(*cub)->ray->dir.x = (*cub)->ray->dir.x * cos(0.3) -  (*cub)->ray->dir.y * sin(0.3);
	(*cub)->ray->dir.y = old_dir * sin(0.3) + (*cub)->ray->dir.y * cos(0.3);
	old_plane = (*cub)->ray->plane.x;
	(*cub)->ray->plane.x = (*cub)->ray->plane.x * cos(0.3) - (*cub)->ray->plane.y * sin(0.3);
	(*cub)->ray->plane.y = old_plane * sin(0.3) + (*cub)->ray->plane.y * cos(0.3);
	//both camera direction and camera plane must be rotated
	// double oldDirX = dirX;
	// dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	// dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	// double oldPlaneX = planeX;
	// planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	// planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

void	hook_right(t_cub **cub)
{
	double	old_dir;
	double	old_plane;

	old_dir = (*cub)->ray->dir.x;
	(*cub)->ray->dir.x = (*cub)->ray->dir.x * cos(-0.3) -  (*cub)->ray->dir.y * sin(-0.3);
	(*cub)->ray->dir.y = old_dir * sin(-0.3) + (*cub)->ray->dir.y * cos(-0.3);
	old_plane = (*cub)->ray->plane.x;
	(*cub)->ray->plane.x = (*cub)->ray->plane.x * cos(-0.3) - (*cub)->ray->plane.y * sin(-0.3);
	(*cub)->ray->plane.y = old_plane * sin(-0.3) + (*cub)->ray->plane.y * cos(-0.3);
	//both camera direction and camera plane must be rotated
	// double oldDirX = dirX;
	// dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	// dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	// double oldPlaneX = planeX;
	// planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	// planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}
