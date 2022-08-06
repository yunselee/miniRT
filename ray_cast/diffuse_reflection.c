/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_reflection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:22:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 15:35:35 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"

static double	diffuse_helper(t_obj_base *objlst, \
							t_light *target_light, \
							t_vec3 normal, \
							t_vec3 intersection)
{
	t_obj_base	*target_obj;
	t_vec3		dir_to_light;
	double		dist[2];
	double		diffuse;
	t_ray		ray_to_light;

	dist[0] = INFINITY;
	dir_to_light = (v3_sub(target_light->o, intersection));
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = intersection;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = intersect(ray_to_light, target_obj, NULL);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
			dist[0] = dist[1];
		target_obj = target_obj->next;
	}
	if (isnan(dist[0]) == FALSE && dist[0] < v3_l2norm(dir_to_light))
		return (0);
	diffuse = fmax(0, v3_dot(v3_normalize(dir_to_light), normal));
	diffuse *= target_light->bright;
	return (diffuse);
}

t_color	diffuse_light(t_scene *scene, \
					t_obj_base *hit_obj, \
					t_vec3 normal, t_vec3 \
					intersection)
{
	t_light	*light;
	t_color	color;
	t_color	color_temp;
	double	diffuse;

	color = rgb_color(0, 0, 0);
	light = scene->light;
	while (light != NULL)
	{
		diffuse = diffuse_helper(scene->obj, light, normal, intersection);
		if (diffuse > EPSILON)
		{
			color_temp.red = round((double)light->color.red / 255 \
									* hit_obj->color.red);
			color_temp.green = round((double)light->color.green / 255 \
									* hit_obj->color.green);
			color_temp.blue = round((double)light->color.blue / 255 \
									* hit_obj->color.blue);
			color_temp = color_scale(color_temp, diffuse);
			color = color_add(color, color_temp);
		}
		light = light->next;
	}
	return (color);
}
