/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 05:05:37 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 20:48:54 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "../LIBFT/libft.h"
#include "../Libft_vector/transform.h"
#include <stdio.h>

static void	put_mat33(t_mat33 m)
{
	printf("⎡% 3.3f % 3.3f % 3.3f⎤\n", m.r1.x, m.r2.x, m.r3.x);
	printf("⎢% 3.3f % 3.3f % 3.3f⎥\n", m.r1.y, m.r2.y, m.r3.y);
	printf("⎣% 3.3f % 3.3f % 3.3f⎦\n", m.r1.z, m.r2.z, m.r3.z);
}

static t_mat33	get_transformation_mat(t_vec3 k)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_mat33	mat;

	w = v3_normalize(k);
	u = make_v3(0, 1, 0);
	if (1.0 == w.z)
		v = make_v3(1, 0, 0);
	else if (-1.0 == w.z)
		v = make_v3(-1, 0, 0);
	else
	{
		u = make_v3(w.y, -w.x, 0);
		u = v3_normalize(u);
		v = v3_crs(w, u);
	}
	mat = create_mat33(u, v, w);
	return (mat33_trans(mat));
}

static void	transform_lights(t_scene *scene)
{
	t_light	*curr;

	curr = scene->light;
	while (curr)
	{
		// curr->o = v3_sub((curr->o), (scene->cam->pos));
		curr->o = transform_by_mat33((scene->global), (curr->o));
		curr = curr->next;
	}
}

static void	transform_objects(t_scene *scene)
{
	t_obj_base	*curr;

	curr = scene->obj;
	while (curr)
	{
		// curr->o = v3_sub((curr->o), (scene->cam->pos));
		curr->o = transform_by_mat33((scene->global), (curr->o));
		curr->n = transform_by_mat33((scene->global), (curr->n));
		curr = curr->next;
	}
}

int	transform_to_cam_cord(t_scene *scene)
{
	scene->global = get_transformation_mat((scene->cam->dir));
	printf("Tranformation Matrix : \n");
	put_mat33(scene->global);
	printf("\n");
	transform_lights(scene);
	transform_objects(scene);
	scene->cam->pos = transform_by_mat33((scene->global), (scene->cam->pos));
	// scene->cam->pos = v3_sub((scene->cam->pos), (scene->cam->pos));
	scene->cam->dir = transform_by_mat33((scene->global), (scene->cam->dir));
	return (TRUE);
}
