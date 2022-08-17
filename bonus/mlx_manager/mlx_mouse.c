/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:48:44 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 09:00:50 by dkim2            ###   ########.fr       */
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

static t_quadrics	*select_object(int x, int y)
{
	const t_scene	*scene = get_scene();
	t_ray			ray;
	double			d;

	get_scene_editer()->selected_quad = NULL;
	d = ((double)WIN_WIDTH / 2) / tan(scene->cam->hfov / 2);
	ray.dir = make_v3(x - WIN_WIDTH / 2, y - WIN_HEIGHT / 2, d);
	ray.dir = v3_normalize(ray.dir);
	ray.org = scene->cam->pos;
	get_intersect_distance(scene->quads, &(get_scene_editer()->selected_quad), ray);
	return (get_scene_editer()->selected_quad);
}

int	mousedown(int button, int x, int y)
{
	printf("mouse clicked\n");
	if (x < 0 || y < 0 || (unsigned int)x > WIN_WIDTH \
		|| (unsigned int)y > WIN_HEIGHT || get_scene_editer()->edit == FALSE \
		|| get_scene_editer()->target_scene == E_NONE)
		return (FALSE);
	get_scene_editer()->clicked = button;
	get_scene_editer()->prev_pixel[0] = x;
	get_scene_editer()->prev_pixel[1] = y;
	if (button == MOUSE_LEFT && get_scene_editer()->target_scene == E_OBJ)
	{
		printf("selected object : \n");
		if (select_object(x, y) == NULL)
			printf("\tNONE\n");
		else
			print_single_quadrics(get_scene_editer()->selected_quad);
	}
	else if (button == MOUSE_WHELL_DOWN || button == MOUSE_WHELL_UP)
	{
		if (mlx_mouse_wheel(button) == FALSE)
			return (FALSE);
	}
	else
		return (FALSE);
	mlx_renew_image(get_mlx());
	return (TRUE);
}

int	mouseup(int button, int x, int y)
{
	if (x > 0 && y > 0 && button > 0)
	{
		get_scene_editer()->clicked = 0;
		printf("mouse outed\n");
	}
	return (FALSE);
}

int	mousemove(int x, int y)
{
	double	dx;
	double	dy;
	t_vec3	axis;

	if (get_scene_editer()->edit == FALSE || get_scene_editer()->clicked != 1)
		return (FALSE);
	dx = x - get_scene_editer()->prev_pixel[0];
	dy = y - get_scene_editer()->prev_pixel[1];
	get_scene_editer()->prev_pixel[0] = x;
	get_scene_editer()->prev_pixel[1] = y;
	if (dx == 0 && dy == 0)
		return (0);
	axis = v3_normalize(make_v3(-dy, dx, 0));
	if (fabs(dx) > fabs(dy))
		axis = v3_normalize(make_v3(0, dx, 0));
	if (get_scene_editer()->target_scene == E_CAM)
		transform_to_cam_cord(get_scene(), \
			mat33_trans(rotation_mat33(axis, -3)));
	else if (get_scene_editer()->target_scene == E_OBJ && get_scene_editer()->selected_quad != NULL)
		rotate_quadrics(get_scene_editer()->selected_quad, axis, -3);
	print_info_camera(get_scene()->cam);
	mlx_renew_image(get_mlx());
	return (1);
}
