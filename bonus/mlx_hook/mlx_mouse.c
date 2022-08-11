/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:48:44 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 02:50:36 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "transform.h"
#include "print_info.h"
#include "quadrics.h"

static t_quadrics	*select_object(t_mlx *mlx, int x, int y)
{
	t_ray	ray;
	double	d;

	mlx->selected_quad = NULL;
	d = ((double)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2);
	ray.dir = make_v3(x - (int)mlx->width / 2, y - (int)mlx->height / 2, d);
	ray.dir = v3_normalize(ray.dir);
	ray.org = mlx->scene->cam->pos;
	get_intersect_distance(mlx->scene->quads, &(mlx->selected_quad), ray);
	return (mlx->selected_quad);
}

int	mousedown(int button, int x, int y, t_mlx *mlx)
{
	printf("mouse clicked\n");
	if (!mlx || x < 0 || y < 0 || (unsigned int)x > mlx->width \
		|| (unsigned int)y > mlx->height || mlx->edit == FALSE \
		|| mlx->target_scene == E_NONE)
		return (FALSE);
	mlx->clicked = button;
	mlx->last[0] = x;
	mlx->last[1] = y;
	if (button == MOUSE_LEFT && mlx->target_scene == E_OBJ)
	{
		printf("selected object : \n");
		if (select_object(mlx, x, y) == NULL)
			printf("\tNONE\n");
		else
			print_single_quadrics(mlx->selected_quad);
	}
	else if (button == MOUSE_WHELL_DOWN || button == MOUSE_WHELL_UP)
	{
		if (mlx_mouse_wheel(mlx, button) == FALSE)
			return (FALSE);
	}
	else
		return (FALSE);
	mlx_renew_image(mlx);
	return (TRUE);
}

int	mouseup(int button, int x, int y, t_mlx *mlx)
{
	if (x > 0 && y > 0 && button > 0)
	{
		mlx->clicked = 0;
		printf("mouse outed\n");
	}
	return (FALSE);
}

int	mousemove(int x, int y, t_mlx *mlx)
{
	double	dx;
	double	dy;
	t_vec3	axis;

	if (mlx->edit == FALSE || mlx->clicked != 1)
		return (FALSE);
	dx = x - mlx->last[0];
	dy = y - mlx->last[1];
	mlx->last[0] = x;
	mlx->last[1] = y;
	if (dx == 0 && dy == 0)
		return (0);
	axis = v3_normalize(make_v3(-dy, 0, 0));
	if (fabs(dx) > fabs(dy))
		axis = v3_normalize(make_v3(0, dx, 0));
	if (mlx->target_scene == E_CAM)
		transform_to_cam_cord(mlx->scene, \
			mat33_trans(rotation_mat33(axis, -3)));
	else if (mlx->target_scene == E_OBJ && mlx->selected_quad != NULL)
	{
		mlx->selected_quad->dir = rotate_vec3_deg(axis, -3, \
									mlx->selected_quad->dir);
		mlx->selected_quad->tan = rotate_vec3_deg(axis, -3, \
									mlx->selected_quad->tan);
		rotate_quadrics(mlx->selected_quad, axis, -3);
	}
	print_info_camera(mlx->scene->cam);
	mlx_renew_image(mlx);
	return (1);
}
