/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_wheel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:24:58 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/07 13:53:09 by dkim2            ###   ########.fr       */
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

static int	wheel_object(t_mlx *mlx, int keycode)
{
	double	stride;
	
	stride = 0.05;
	if (mlx->selected_obj == NULL)
		return (FALSE);
	if (keycode == 5)
		stride = 1 - stride;
	else
		stride = 1 + stride;
	if (mlx->selected_obj->h > EPSILON && mlx->selected_obj->r > EPSILON)
	{
		mlx->selected_obj->h *= stride;
		mlx->selected_obj->r *= stride;
	}
	return (TRUE);
}

int mlx_mouse_wheel(t_mlx *mlx, int keycode)
{
	if (keycode < 4)
		return (FALSE);
	else if (mlx->target_scene == E_CAM)
		wheel_camera(mlx, keycode);
	else if (mlx->target_scene == E_LIGHT)
	{

	}
	else if (mlx->target_scene == E_OBJ)
		return (wheel_object(mlx, keycode));
	else
		return (FALSE);
	return (TRUE);
}