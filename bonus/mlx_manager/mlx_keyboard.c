/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:36:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/24 15:49:11 by yunselee         ###   ########.fr       */
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
#include "debug_msgs.h"

static int	chage_to_editmode(int keycode)
{
	t_scene_editer	*editer;

	editer = get_scene_editer();
	if (keycode == KEY_D)
	{
		editer->debug = (editer->debug + 1) % 3;
		if (editer->debug == D_NONE)
			printf("\033[1;3m\tDEBUG MODE OFF\033[0m\n");
		else if (editer->debug == D_SIMPLE)
			printf("\033[1;3m\tDEBUG MODE ON : SIMPLE mode\033[0m\n");
		else if (editer->debug == D_DETAIL)
			printf("\033[1;3m\tDEBUG MODE ON : DETAIL mode\033[0m\n");
		if (editer->debug != D_NONE)
			printf("\033[1;3m\tclick pixels with mouse\n \
right button to see detail\033[0m\n");
		return (TRUE);
	}
	editer->debug = FALSE;
	editer->edit = ceil(fmax(WIN_WIDTH, WIN_HEIGHT) / 500);
	printf("\033[1;3m\tNow in editting mode\n");
	printf("\tSelect scene to edit -> C : cam, L : light, O : objs\n");
	printf("\tPress R to render image\033[0m\n");
	mlx_renew_image();
	return (TRUE);
}

static int	change_to_rendermode(void)
{
	t_scene_editer	*scene_editer;

	scene_editer = get_scene_editer();
	scene_editer->edit = 0;
	scene_editer->target_scene = E_NONE;
	scene_editer->selected_light = NULL;
	scene_editer->selected_quad = NULL;
	printf("\033[1;3m\tREDERING.....\033[0m\n");
	mlx_renew_image();
	printf("\033[1;3m\tDONE\n");
	printf("\tpress E to edit scene or press D to change debug mode\033[0m\n");
	return (TRUE);
}

static int	set_edit_scene(int keycode)
{
	t_scene_editer	*editer;

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
		edit_mode_info_camera();
	else if (keycode == KEY_L)
	{
		edit_mode_info_light();
		editer->selected_light = get_scene()->light;
		print_single_light(editer->selected_light);
	}
	else if (keycode == KEY_O)
		edit_mode_info_object();
	mlx_renew_image();
	return (TRUE);
}

static int	move_target_scene(int keycode)
{
	const enum e_target	target_scene = get_scene_editer()->target_scene;

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
	t_scene_editer	*editer;

	editer = get_scene_editer();
	if (keycode == ESC)
		terminate_mlx(NULL);
	else if (editer->edit == 0 && (keycode == KEY_E || keycode == KEY_D))
		return (chage_to_editmode(keycode));
	else if (editer->edit != 0 && keycode == KEY_R)
		return (change_to_rendermode());
	else if (editer->edit != 0 && editer->target_scene == E_NONE)
		return (set_edit_scene(keycode));
	else if (editer->edit != 0 && keycode == ENTER)
	{
		editer->target_scene = E_NONE;
		printf("\033[1;3m\tSCENE EDITING DONE! press R to render\n");
		printf("\tor Select scene to edit -> C : cam, L : light, \
O : objs\033[0m\n");
		mlx_renew_image();
		return (1);
	}
	else if (editer->edit != 0 && editer->target_scene == E_LIGHT \
			&& keycode == SPACE)
		mlx_replace_light();
	return (move_target_scene(keycode));
}
