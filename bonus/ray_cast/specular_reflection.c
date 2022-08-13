/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:20:20 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 18:58:24 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include "scene.h"

#include <stdio.h>

static float	specular_helper(t_quadrics *objlst, \
								const t_light *target_light, \
								t_vec3 mirror_ray, \
								t_vec3 hit_point)
{
	t_quadrics		*target_obj;
	t_vec3			dir_to_light;
	t_ray			ray_to_light;
	float			dist[2];
	float			specular;

	dist[0] = INFINITY;
	dir_to_light = v3_sub(target_light->o, hit_point);
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = hit_point;
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
	specular = fmax(0, v3_dot(v3_normalize(dir_to_light), mirror_ray));
	return (specular);
}

t_color	specular_light(const t_scene *scene, t_quadrics *hit_obj, \
						t_vec3 mirror_ray, t_vec3 hit_point)
{
	const t_light	*light;
	t_color	color;
	t_color	color_temp;
	float	specular;

	color = rgb_color(0, 0, 0);
	light = scene->light;
	while (light)
	{
		specular = specular_helper(scene->quads, light, mirror_ray, hit_point);
		specular = (hit_obj->spec_rs) * pow(specular, hit_obj->spec_ns);
		if (specular > EPSILON)
		{
			color_temp.red = roundf((float)light->color.red / 255 \
									* light->color.red);
			color_temp.green = roundf((float)light->color.green / 255 \
									* light->color.green);
			color_temp.blue = roundf((float)light->color.blue / 255 \
									* light->color.blue);
			color_temp = color_scale(color_temp, specular);
			color = color_add(color, color_temp);
		}
		light = light->next;
	}
	return (color);
}
