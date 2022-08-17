/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:36:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 12:56:00 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx_manager.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "transform.h"
#include "print_info.h"
#include "resolution.h"
#include "scene_editer.h"

static int	chage_to_editmode()
{
	get_scene_editer()->edit = ceil(fmax(WIN_WIDTH, WIN_HEIGHT) / 500);
	mlx_renew_image();
	printf("Now in Editting mode. press R to render\n");
	printf("Select scene to edit -> C : cam L : light O : objs\n");
	return (TRUE);
}

static int	change_to_rendermode()
{
	t_scene_editer *scene_editer;

	scene_editer = get_scene_editer();
	scene_editer->edit = 0;
	scene_editer->target_scene = E_NONE;
	scene_editer->selected_light = NULL;
	scene_editer->selected_quad = NULL;
	printf("REDERING.....\n");
	mlx_renew_image();
	printf("DONE\n");
	return (TRUE);
}

static int	set_edit_scene(int keycode)
{
	t_scene_editer *editer;

	editer = get_scene_editer();
	if (keycode == KEY_C)
		editer->target_scene = E_CAM;
	else if (keycode == KEY_L)
		editer->target_scene = E_LIGHT;
	else if (keycode == KEY_O)
		editer->target_scene = E_OBJ;
	else
		return (FALSE);
	if (keycode == KEY_C)
		printf("mode : CAMERA\n");
	else if (keycode == KEY_L)
	{
		printf("mode : LIGHT\n");
		editer->selected_light = get_scene()->light;
		print_single_light(editer->selected_light);
	}
	else if (keycode == KEY_O)
		printf("mode : OBJECTS\n");
	mlx_renew_image();
	return (TRUE);
}

static int	move_target_scene(int keycode)
{
	const enum e_target target_scene = get_scene_editer()->target_scene;

	if (target_scene == E_CAM)
		return (mlx_move_cam(keycode));
	else if (target_scene == E_LIGHT)
		return (mlx_move_light(keycode));
	else if (target_scene == E_OBJ)
		return (mlx_move_obj(keycode));
	else
		return (FALSE);
}

int	keydown(int keycode)
{
	t_scene_editer *editer;

	editer = get_scene_editer();
	if (keycode == ESC)
	{
		destroy_mlx(NULL);
		exit(0);
	}
	else if (editer->edit == 0 && keycode == KEY_E)
		return (chage_to_editmode());
	else if (editer->edit != 0 && keycode == KEY_R)
		return (change_to_rendermode());
	else if (editer->edit != 0 && editer->target_scene == E_NONE)
		return (set_edit_scene(keycode));
	else if (editer->edit != 0 && keycode == ENTER)
	{
		editer->target_scene = E_NONE;
		printf("SCENE EDITING DONE! press R to render\n");
		printf("or Select scene to edit -> C : cam L : light O : objs\n");
		mlx_renew_image();
		return (1);
	}
	else if (editer->edit != 0 && editer->target_scene == E_LIGHT && keycode == SPACE)
		mlx_replace_light();
	return (move_target_scene(keycode));
}
