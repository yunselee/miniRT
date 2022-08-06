/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:36:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 14:13:42 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "transform.h"

static int mlx_move(t_mlx *mlx, int keycode)
{
	const int	stride = 1;
	t_mat33		transform;

	if (mlx->edit == FALSE)
	{
		printf("NOT IN EDIT MODE. PRESS E TO EDIT SCENE\n");
		return (FALSE);
	}
	else if (keycode == KEY_D)
		mlx->scene->cam->pos.x += stride;
	else if (keycode == KEY_A)
		mlx->scene->cam->pos.x -= stride;
	else if (keycode == KEY_W)
		mlx->scene->cam->pos.z += stride;
	else if (keycode == KEY_S)
		mlx->scene->cam->pos.z -= stride;
	else if (keycode == UARROW)
		mlx->scene->cam->pos.y -= stride;
	else if (keycode == DARROW)
		mlx->scene->cam->pos.y += stride;
	else if (keycode == KEY_Q)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), 5, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), 5, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	else if (keycode == KEY_E)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), -5, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), -5, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	else
		return (FALSE);
	return (TRUE);
}

static int mlx_switch_mode(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_E)
	{
		if (mlx->edit != FALSE)
			return (FALSE);
		printf("Now in EDIT MODE. press R to render mlx->scene\n");
		mlx->edit = ceil(fmax(mlx->width, mlx->height) / 500);
	}
	else if (keycode == KEY_R)
	{
		if (mlx->edit == FALSE)
			return (FALSE);
		printf("Rendering Image....\n");	
		mlx->edit = FALSE;
	}
	else
		return (FALSE);
	return (TRUE);	
}

int	keydown(int keycode, t_mlx *mlx)
{

	if (keycode == ESC)
	{
		delete_mlx(mlx);
		exit(0);
	}
	else if(mlx_switch_mode(mlx, keycode) == TRUE)
	{
		mlx_renew_image(mlx);
		return (TRUE);
	}
	else if (mlx_move(mlx, keycode) == TRUE)
	{
		mlx_renew_image(mlx);
		return (TRUE);
	}
	else
		return (0);
}