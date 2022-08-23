/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 05:05:37 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/23 19:56:02 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "../LIBFT/libft.h"
#include "../Libft_vector/transform.h"
#include <stdio.h>

static void	transform_lights(t_light *light, t_mat33 transform)
{
	light->o = transform_by_mat33(transform, (light->o));
}

static void	transform_objects(t_obj_base *obj, t_mat33 transform)
{
	t_obj_base	*curr;

	curr = obj;
	while (curr)
	{
		curr->o = transform_by_mat33(transform, (curr->o));
		curr->n = transform_by_mat33(transform, (curr->n));
		curr = curr->next;
	}
}

int	transform_to_cam_cord(t_scene *scene, t_mat33 transform)
{
	transform_lights(scene->light, transform);
	transform_objects(scene->obj, transform);
	scene->cam->pos = transform_by_mat33(transform, (scene->cam->pos));
	scene->cam->dir = transform_by_mat33(transform, (scene->cam->dir));
	scene->global = mul_mat33(scene->global, transform);
	return (TRUE);
}
