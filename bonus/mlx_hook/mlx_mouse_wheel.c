/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_wheel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:24:58 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 00:00:32 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "mlx_part.h"

static void	wheel_camera(t_mlx *mlx, int keycode)
{
	int	stride;

	stride = 5;
	mlx->scene->cam->hfov *= (180 / M_PI);
	if (keycode == 5)
		stride = -5;
	if (mlx->scene->cam->hfov + stride > 20 \
		&& mlx->scene->cam->hfov + stride < 160)
		mlx->scene->cam->hfov += stride;
	printf("FOV : %.2f(deg)\n", (mlx->scene->cam->hfov));
	mlx->scene->cam->hfov /= (180 / M_PI);
}

// static int	wheel_object(t_quadrics *obj, int keycode)
// {
// 	double	stride;

// 	stride = 0.05;
// 	if (obj == NULL)
// 		return (FALSE);
// 	if (keycode == 5)
// 		stride = 1 - stride;
// 	else
// 		stride = 1 + stride;
// 	if (obj->h > EPSILON || obj->r > EPSILON)
// 	{
// 		obj->h *= stride;
// 		obj->r *= stride;
// 	}
// 	print_info(obj);
// 	return (TRUE);
// }

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

int	mlx_mouse_wheel(t_mlx *mlx, int keycode)
{
	if (keycode < 4)
		return (FALSE);
	else if (mlx->target_scene == E_CAM)
		wheel_camera(mlx, keycode);
	// else if (mlx->target_scene == E_OBJ)
	// 	return (wheel_object(mlx->selected_quad, keycode));
	else if (mlx->target_scene == E_LIGHT)
		return (wheel_light(mlx->selected_light, keycode));
	else
		return (FALSE);
	return (TRUE);
}
