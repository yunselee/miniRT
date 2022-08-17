/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:48:44 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/17 21:59:20 by dkim2            ###   ########.fr       */
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
#include "quadrics.h"
#include "resolution.h"
#include "scene_editer.h"
#include "debug_msgs.h"

static int	debug_single_raycast(t_mlx *mlx, int x, int y)
{
	const	t_cam	*cam = get_scene()->cam;
	t_ray	ray;
	float	d;

	printf("DEBUG MODE\n");
	d = ((float)WIN_WIDTH / 2) / tan(cam->hfov / 2);
	ray.dir = make_v3(x - WIN_WIDTH / 2, y - WIN_HEIGHT / 2, d);
	ray.dir = v3_normalize(ray.dir);
	ray.org = cam->pos;
	single_ray_cast(mlx, ray);
	return (TRUE);
}

static t_quadrics	*select_object(int x, int y)
{
	const t_scene	*scene = get_scene();
	t_ray			ray;
	float			d;

	get_scene_editer()->selected_quad = NULL;
	d = ((float)WIN_WIDTH / 2) / tan(scene->cam->hfov / 2);
	ray.dir = make_v3(x - WIN_WIDTH / 2, y - WIN_HEIGHT / 2, d);
	ray.dir = v3_normalize(ray.dir);
	ray.org = scene->cam->pos;
	get_intersect_distance(scene->quads, &(get_scene_editer()->selected_quad), ray);
	return (get_scene_editer()->selected_quad);
}

int	mousedown(int button, int x, int y)
{
	t_scene_editer *editer;

	editer= get_scene_editer();

	if (x < 0 || y < 0 || (unsigned int)x > WIN_WIDTH \
		|| (unsigned int)y > WIN_HEIGHT \
		|| (((mlx->edit == FALSE) || (mlx->target_scene == E_NONE)) && (mlx->debug == FALSE)))
		return (FALSE);
	printf("mouse clicked\n");
	mlx->clicked = button;
	mlx->prev_pixel[0] = x;
	mlx->prev_pixel[1] = y;
	if (mlx->debug != D_NONE && button == MOUSE_RIGHT)
		return (debug_single_raycast(mlx, x, y));
	if (button == MOUSE_LEFT && mlx->target_scene == E_OBJ)
	{
		select_object(mlx, x, y);
		printf("selected object : \n");
		print_single_quadrics(mlx->selected_quad);
	}
	else if (button == MOUSE_WHELL_DOWN || button == MOUSE_WHELL_UP)
	{
		if (mlx_mouse_wheel(button) == FALSE)
			return (FALSE);
	}
	else
		return (FALSE);
	mlx_renew_image();
	return (TRUE);
}

int	mouseup(int button, int x, int y)
{
	if (x > 0 && y > 0 && button > 0)
	{
		get_scene_editer()->clicked = 0;
		printf("mouse unclicked\n");
	}
	return (FALSE);
}

int	mousemove(int x, int y)
{
	double	dx;
	double	dy;
	t_vec3	axis;
	t_scene_editer *editer;
	
	editer = get_scene_editer();
	if (editer->edit == FALSE || editer->clicked != 1)
		return (FALSE);
	dx = x - editer->prev_pixel[0];
	dy = y - editer->prev_pixel[1];
	editer->prev_pixel[0] = x;
	editer->prev_pixel[1] = y;
	if (dx == 0 && dy == 0)
		return (0);
	axis = v3_normalize(make_v3(-dy, dx, 0));
	if (fabs(dx) > fabs(dy))
		axis = v3_normalize(make_v3(0, dx, 0));
	if (editer->target_scene == E_CAM)
		transform_to_cam_cord(get_scene(), \
			mat33_trans(rotation_mat33(axis, -3)));
	else if (editer->target_scene == E_OBJ && editer->selected_quad != NULL)
		rotate_quadrics(editer->selected_quad, axis, -3);
	print_info_camera(get_scene()->cam);
	mlx_renew_image(get_mlx());
	return (1);
}
