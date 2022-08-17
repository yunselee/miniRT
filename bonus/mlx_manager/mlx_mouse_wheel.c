/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_wheel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:24:58 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 15:36:30 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "mlx_manager.h"
#include "matrix44.h"
#include "print_info.h"
#include "scene_editer.h"
#include "resolution.h"

static void	wheel_camera(int keycode)
{
	int		stride;
	t_cam	*cam;

	cam = get_scene()->cam;
	stride = 5;
	cam->hfov *= (180 / M_PI);
	if (keycode == 5)
		stride = -5;
	if (cam->hfov + stride > 20 \
		&& cam->hfov + stride < 160)
		cam->hfov += stride;
	printf("FOV : %.2f(deg)\n", (cam->hfov));
	cam->hfov /= (180 / M_PI);
	cam->cam_proportion = (WIN_WIDTH / 2) / tan(cam->hfov / 2);
}

static int	wheel_object(t_quadrics *obj, int keycode)
{
	double	stride;
	t_mat44	mat;

	stride = 0.1;
	if (obj == NULL || obj->type == Q_PLANE)
		return (FALSE);
	if (keycode == 5)
		stride = 1 - stride;
	else
		stride = 1 + stride;
	stride = 1 / stride;
	mat.col1 = make_v4(1, 0, 0, 0);
	mat.col2 = make_v4(0, 1, 0, 0);
	mat.col3 = make_v4(0, 0, 1, 0);
	mat.col4 = make_v4(0, 0, 0, 1 / stride);
	
	if (obj->range_z[1] - obj->range_z[0] > EPSILON)
	{
		obj->range_z[0] /= stride;
		obj->range_z[1] /= stride;
		obj->coefs = mul_mat44(mat, mul_mat44(obj->coefs, mat));
	}
	print_single_quadrics(obj);
	return (TRUE);
}

static int	wheel_light(t_light *light, int keycode)
{
	double	stride;

	stride = 0.05;
	if (light == NULL)
		return (FALSE);
	if (keycode == 5)
		stride = -0.1;
	else
		stride = 0.1;
	if (light->bright + stride > 0 \
		&& light->bright + stride < 1)
	{
		light->bright += stride;
		printf("\tbrightness : \033[2;38;2;%d;%d;%dm%.2f\033[0m\n", \
				light->color.red, \
				light->color.green, \
				light->color.blue, \
				light->bright);
	}
	return (TRUE);
}

int	mlx_mouse_wheel(int keycode)
{
	if (keycode < 4)
		return (FALSE);
	else if (get_scene_editer()->target_scene == E_CAM)
		wheel_camera(keycode);
	else if (get_scene_editer()->target_scene == E_OBJ)
		return (wheel_object(get_scene_editer()->selected_quad, keycode));
	else if (get_scene_editer()->target_scene == E_LIGHT)
		return (wheel_light(get_scene_editer()->selected_light, keycode));
	else
		return (FALSE);
	return (TRUE);
}
