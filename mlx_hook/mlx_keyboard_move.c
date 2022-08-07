/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:52:32 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/07 13:19:46 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_part.h"
#include "mlx_keycode.h"
#include "transform.h"
#include <stdio.h>

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

int	mlx_move_cam(t_mlx *mlx, int keycode)
{
	t_mat33		transform;

	if (keycode == KEY_Q)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), 1, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), 1, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	else if (keycode == KEY_E)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), -1, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), -1, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	else if (move_pos(&(mlx->scene->cam->pos), keycode) == FALSE)
		return (FALSE);
	mlx_renew_image(mlx);
	return (TRUE);
}

int	mlx_move_light(t_mlx *mlx, int keycode)
{
	if (move_pos(&(mlx->scene->light->o), keycode) == FALSE)
		return (FALSE);
	mlx_renew_image(mlx);
	return (TRUE);
}

int	mlx_move_obj(t_mlx *mlx, int keycode)
{
	if (mlx->selected_obj == NULL)
		return (FALSE);
	else if (keycode == KEY_Q && mlx->selected_obj->type != E_SPHERE)
		mlx->selected_obj->n = rotate_vec3_deg(make_v3(0, 0, 1), -1, \
												mlx->selected_obj->n);
	else if (keycode == KEY_E && mlx->selected_obj->type != E_SPHERE)
		mlx->selected_obj->n = rotate_vec3_deg(make_v3(0, 0, 1), 1, \
												mlx->selected_obj->n);
	else if (move_pos(&(mlx->selected_obj->o), keycode) == FALSE)
		return (FALSE);
	mlx_renew_image(mlx);
	return (TRUE);
}
