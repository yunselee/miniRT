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

static t_obj_base	*select_obj(t_scene *scene, t_ray ray)
{
	t_obj_base	*intersect_obj;
	double		dist;

	intersect_obj = NULL;
	dist = get_intersect_distance(scene->obj, &intersect_obj, ray);
	if (isinf(dist) == TRUE)
		return (NULL);
	return (intersect_obj);
}

int	mousedown(int button, int x, int y, t_mlx *mlx)
{
	t_ray	ray;
	if (!mlx || x < 0 || y < 0 || (unsigned int)x > mlx->width \
			|| (unsigned int)y > mlx->height || mlx->edit == FALSE)
		return (0);
	mlx->clicked = button;
	mlx->scene->cam->hfov *= (180 / M_PI);
	if (button == 1)
	{
		mlx->last[0] = x;
		mlx->last[1] = y;
		ray.dir = make_v3(x - mlx->width / 2 , y - mlx->height , \
					((double)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2));
		ray.dir = v3_normalize(ray.dir);
		ray.org = mlx->scene->cam->pos;
		mlx->selected_obj = select_obj(mlx->scene, ray);
		if (mlx->selected_obj  == NULL)
			printf("selected object : NONE\n");
		else
			printf("selected object : %u\n", mlx->selected_obj->type);
	}
	if (button == 4)
	{
		if (mlx->scene->cam->hfov < 160)
			mlx->scene->cam->hfov += 5;
		printf("FOV : %.2f(deg)\n", (mlx->scene->cam->hfov));
	}
	else if (button == 5)
	{
		if (mlx->scene->cam->hfov > 20)
			mlx->scene->cam->hfov -= 5;
		printf("FOV : %.2f(deg)\n", (mlx->scene->cam->hfov));
	}
	mlx->scene->cam->hfov /= (180 / M_PI);	
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
			transform.r1 = rotate_vec3_deg(axis, -3, make_v3(1, 0, 0));
			transform.r2 = rotate_vec3_deg(axis, -3, make_v3(0, 1, 0));
			transform.r3 = rotate_vec3_deg(axis, -3, make_v3(0, 0, 1));
			transform_to_cam_cord(mlx->scene, mat33_trans(transform));
		}
		else
			mlx->selected_obj->n = rotate_vec3_deg(axis, -3, mlx->selected_obj->n);
	}
	mlx_renew_image(mlx);
	return (1);
}