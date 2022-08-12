/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_reflection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:22:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 12:18:52 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"

static float	diffuse_helper(t_quadrics *objlst, \
							t_light *target_light, \
							t_vec3 normal, \
							t_vec3 intersection)
{
	t_quadrics	*target_obj;
	t_vec3		dir_to_light;
	t_ray		ray_to_light;
	double		diffuse;
	double		dist[3];

	dist[0] = INFINITY;
	dir_to_light = v3_sub(target_light->o, intersection);
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = intersection;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = find_intersection(target_obj, &ray_to_light);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
			dist[0] = dist[1];
		target_obj = target_obj->next;
	}
	if (isnan(dist[0]) == FALSE && dist[0] < v3_l2norm(dir_to_light) + EPSILON)
		return (0);
	diffuse = fmax(0, v3_dot(v3_normalize(dir_to_light), normal));
	diffuse *= target_light->bright;
	return (diffuse);
}

t_color	diffuse_light(const t_scene *scene, \
					t_quadrics *hit_obj, \
					t_vec3 normal, \
					t_vec3 intersection)
{
	t_light	*light;
	t_color	color;
	t_color	clr_tmp;
	float	diffuse;

	intersection = v3_add(intersection, v3_mul(normal, EPSILON));
	color = rgb_color(0, 0, 0);
	clr_tmp = color_disruption(hit_obj, intersection);
	light = scene->light;
	while (light != NULL)
	{
		diffuse = diffuse_helper(scene->quads, light, normal, intersection);
		if (diffuse > EPSILON)
		{
			clr_tmp.red = roundf((float)light->color.red / 255 * clr_tmp.red);
			clr_tmp.green = roundf((float)light->color.green / 255 \
									* clr_tmp.green);
			clr_tmp.blue = roundf((float)light->color.blue / 255 \
									* clr_tmp.blue);
			clr_tmp = color_scale(clr_tmp, diffuse * (1 - hit_obj->spec_rs));
			color = color_add(color, clr_tmp);
		}
		light = light->next;
	}
	return (color);
}
