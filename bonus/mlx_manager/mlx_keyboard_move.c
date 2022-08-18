/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:52:32 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/18 14:19:46 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_manager.h"
#include "mlx_keycode.h"
#include "transform.h"
#include <stdio.h>
#include "print_info.h"
#include "quadrics.h"
#include "scene_editer.h"

static int	move_pos(t_vec3 *pos, int keycode)
{
	if (keycode == KEY_D)
		pos->x += 1;
	else if (keycode == KEY_A)
		pos->x -= 1;
	else if (keycode == KEY_W)
		pos->z += 1;
	else if (keycode == KEY_S)
		pos->z -= 1;
	else if (keycode == UARROW)
		pos->y -= 1;
	else if (keycode == DARROW)
		pos->y += 1;
	else
		return (FALSE);
	return (TRUE);
}

int	mlx_move_cam(int keycode)
{
	t_mat33		transform;
	t_scene		*scene;

	scene = get_scene();
	if (keycode == KEY_Q)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), 1, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), 1, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(scene, mat33_trans(transform));
	}
	else if (keycode == KEY_E)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), -1, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), -1, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(scene, mat33_trans(transform));
	}
	else if (move_pos(&(scene->cam->pos), keycode) == FALSE)
		return (FALSE);
	print_info_camera(scene->cam);
	mlx_renew_image();
	return (TRUE);
}

int	mlx_move_light(int keycode)
{
	if (move_pos(&(get_scene_editer()->selected_light->o), keycode) == FALSE)
		return (FALSE);
	print_info_light(get_scene_editer()->selected_light);
	mlx_renew_image();
	return (TRUE);
}

int	mlx_move_obj(int keycode)
{
	const t_vec3	axis = make_v3(0, 0, 1);
	t_quadrics *selected_quad;

	selected_quad = get_scene_editer()->selected_quad;
	if (selected_quad == NULL)
		return (FALSE);
	else if (keycode == KEY_C)
		selected_quad->disruption ^= 0b1;
	else if (keycode == KEY_Q)
		rotate_quadrics(selected_quad, axis, -3);
	else if (keycode == KEY_E)
		rotate_quadrics(selected_quad, axis, 3);
	else if (move_pos(&(selected_quad->org), keycode) == FALSE)
		return (FALSE);
	print_single_quadrics(selected_quad);
	mlx_renew_image();
	return (TRUE);
}

// void	mlx_replace_light()
// {
// 	t_light *selected_light;
	
// 	selected_light = get_scene_editer()->selected_light;
// 	selected_light = selected_light->next;
// 	if (selected_light == NULL)
// 		selected_light = get_scene()->light;
// 	printf("light changed\n");
// 	print_single_light(selected_light);
// }

void	mlx_replace_light()
{
	t_light **selected_light;
	
	selected_light = &(get_scene_editer()->selected_light);
	*selected_light = (*selected_light)->next;
	if (*selected_light == NULL)
		*selected_light = get_scene()->light;
	printf("light changed\n");
	print_single_light(*selected_light);
}
