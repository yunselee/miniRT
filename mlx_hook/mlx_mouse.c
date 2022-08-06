#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "transform.h"

/*
	left        : 1
	right       : 2
	wheel click : 3
	wheel down  : 4
	wheel up    : 5
*/

int	mousedown(int button, int x, int y, t_mlx *mlx)
{
	if (!mlx || x < 0 || y < 0 || mlx->edit == FALSE)
		return (0);
	mlx->clicked = button;
	mlx->scene->cam->hfov *= (180 / M_PI);
	if (button == 1)
	{
		mlx->last[0] = x;
		mlx->last[1] = y;
	}
	if (button == 4)
	{
		if (mlx->scene->cam->hfov < 160)
			mlx->scene->cam->hfov += 5;
	}
	else if (button == 5)
	{
		if (mlx->scene->cam->hfov > 20)
			mlx->scene->cam->hfov -= 5;
	}
	mlx->scene->cam->hfov /= (180 / M_PI);	
	printf("FOV : %.2f(deg)\n", (mlx->scene->cam->hfov * (180 / M_PI)));
	mlx_renew_image(mlx);
	return (1);
}

int	mouseup(int button, int x, int y, t_mlx *mlx)
{
	if (x > 0 && y > 0 && button > 0)
		mlx->clicked = 0;
	return (0);
}

int	mousemove(int x, int y, t_mlx *mlx)
{
	double	dx;
	double	dy;
	t_vec3	axis;
	t_mat33 transform;
	
	if (mlx->edit == FALSE)
		return (0);
	else if (mlx->clicked == 2)
	{
		dx = x - mlx->last[0];
		dy = y - mlx->last[1];
		if (dx == 0 && dy == 0)
			return (0);
		axis = v3_normalize(make_v3(-dy, dx, 0));
		mlx->last[0] = x;
		mlx->last[1] = y;
		transform.r1 = rotate_vec3_deg(axis, -3, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(axis, -3, make_v3(0, 1, 0));
		transform.r3 = rotate_vec3_deg(axis, -3, make_v3(0, 0, 1));
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	mlx_renew_image(mlx);
	return (1);
}