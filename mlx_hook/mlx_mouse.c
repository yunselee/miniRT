#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "transform.h"
#include "print_info.h"

/*
	left        : 1
	right       : 2
	wheel click : 3
	wheel down  : 4
	wheel up    : 5
*/
int	mousedown(int button, int x, int y, t_mlx *mlx)
{
	t_ray	ray;
	double	d;

	if (!mlx || x < 0 || y < 0 || (unsigned int)x > mlx->width \
		|| (unsigned int)y > mlx->height || mlx->edit == FALSE || mlx->target_scene == E_NONE)
		return (0);
	mlx->clicked = button;
	if (button == 1 && mlx->target_scene == E_OBJ)
	{
		d = ((double)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2);
		ray.dir = make_v3(x - (int)mlx->width / 2 , y - (int)mlx->height / 2 , d);
		ray.dir = v3_normalize(ray.dir);
		ray.org = mlx->scene->cam->pos;
		get_intersect_distance(mlx->scene->obj, &(mlx->selected_obj), ray);
		if (mlx->selected_obj == NULL)
			printf("selected object : NONE\n");
		else
		{
			printf("selected object : \n");
			print_info_single_object(mlx->selected_obj);
		}
	}
	else if (button == 2)
	{
		mlx->last[0] = x;
		mlx->last[1] = y;
	}
	else if (button == 4)
	{
		mlx->scene->cam->hfov *= (180 / M_PI);
		if (mlx->scene->cam->hfov < 160)
			mlx->scene->cam->hfov += 5;
		printf("FOV : %.2f(deg)\n", (mlx->scene->cam->hfov));
		mlx->scene->cam->hfov /= (180 / M_PI);	
	}
	else if (button == 5)
	{
		mlx->scene->cam->hfov *= (180 / M_PI);
		if (mlx->scene->cam->hfov > 20)
			mlx->scene->cam->hfov -= 5;
		printf("FOV : %.2f(deg)\n", (mlx->scene->cam->hfov));
		mlx->scene->cam->hfov /= (180 / M_PI);	
	}
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
	else if (mlx->clicked == 2 && mlx->selected_obj == NULL)
	{
		dx = x - mlx->last[0];
		dy = y - mlx->last[1];
		if (dx == 0 && dy == 0)
			return (0);
		axis = v3_normalize(make_v3(-dy, dx, 0));
		mlx->last[0] = x;
		mlx->last[1] = y;
		if (mlx->selected_obj == NULL)
		{
			transform.r1 = rotate_vec3_deg(axis, -1, make_v3(1, 0, 0));
			transform.r2 = rotate_vec3_deg(axis, -1, make_v3(0, 1, 0));
			transform.r3 = rotate_vec3_deg(axis, -1, make_v3(0, 0, 1));
			transform_to_cam_cord(mlx->scene, mat33_trans(transform));
		}
		else
			mlx->selected_obj->n = rotate_vec3_deg(axis, -3, mlx->selected_obj->n);
	}
	mlx_renew_image(mlx);
	return (1);
}