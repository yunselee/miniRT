/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:36:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/08 16:24:27 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "transform.h"

static int	chage_to_editmode(t_mlx *mlx)
{
	mlx->edit = ceil(fmax(mlx->width, mlx->height) / 500);
	mlx_renew_image(mlx);
	printf("Now in Editting mode. press R to render\n");
	printf("Select scene to edit -> C : cam L : light O : objs\n");
	return (TRUE);
}

static int	change_to_rendermode(t_mlx *mlx)
{
	mlx->edit = 0;
	mlx->target_scene = E_NONE;
	printf("REDERING.....\n");
	mlx_renew_image(mlx);
	printf("DONE\n");
	return (TRUE);
}

static int	set_edit_scene(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_C)
		mlx->target_scene = E_CAM;
	else if (keycode == KEY_L)
		mlx->target_scene = E_LIGHT;
	else if (keycode == KEY_O)
		mlx->target_scene = E_OBJ;
	else
		return (FALSE);
	if (keycode == KEY_C)
		printf("mode : CAMERA\n");
	else if (keycode == KEY_L)
	{
		printf("mode : LIGHT\n");
		mlx->selected_light = mlx->scene->light;
		printf("\tbrightness : \033[2;38;2;%d;%d;%dm%.2f\033[0m\n", \
				mlx->selected_light->color.red, \
				mlx->selected_light->color.green, \
				mlx->selected_light->color.blue, \
				mlx->selected_light->bright);
	}
	else if (keycode == KEY_O)
		printf("mode : OBJECTS\n");
	mlx_renew_image(mlx);
	return (TRUE);
}

static int	move_target_scene(t_mlx *mlx, int keycode)
{
	if (mlx->target_scene == E_CAM)
		return (mlx_move_cam(mlx, keycode));
	else if (mlx->target_scene == E_LIGHT)
		return (mlx_move_light(mlx, keycode));
	else if (mlx->target_scene == E_OBJ)
		return (mlx_move_obj(mlx, keycode));
	else
		return (FALSE);
}

int	keydown(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
	{
		delete_mlx(mlx);
		exit(0);
	}
	else if (mlx->edit == 0 && keycode == KEY_E)
		return (chage_to_editmode(mlx));
	else if (mlx->edit != 0 && keycode == KEY_R)
		return (change_to_rendermode(mlx));
	else if (mlx->edit != 0 && mlx->target_scene == E_NONE)
		return (set_edit_scene(mlx, keycode));
	else if (mlx->edit != 0 && keycode == ENTER)
	{
		mlx->target_scene = E_NONE;
		printf("SCENE EDITING DONE!\n");
		printf("Select scene to edit -> C : cam L : light O : objs\n");
		printf("or press R to render\n");
		mlx_renew_image(mlx);
		return (1);
	}
	else if (mlx->edit != 0 && mlx->target_scene == E_LIGHT && keycode == SPACE)
	{
		mlx->selected_light = mlx->selected_light->next;
		if (mlx->selected_light == NULL)
			mlx->selected_light = mlx->scene->light;
		printf("light changed\n");
		printf("\tbrightness : \033[2;38;2;%d;%d;%dm%.2f\033[0m\n", \
				mlx->selected_light->color.red, \
				mlx->selected_light->color.green, \
				mlx->selected_light->color.blue, \
				mlx->selected_light->bright);
		return (1);
	}
	else
		return (move_target_scene(mlx, keycode));
}
