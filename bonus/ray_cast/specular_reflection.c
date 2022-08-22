/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:20:20 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/22 19:01:34 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include "scene.h"
#include <assert.h>
#include <stdio.h>
#include "debug_msgs.h"

static t_color	light_specular(const t_light *light, float specular)
{
	t_color	color;

	color = color_scale(light->color, specular * light->bright);
	return (color);
}

static t_color	object_specular(t_ray reflect_ray, \
								int recurse, \
								float specular_rs)
{
	t_color	color;

	color = single_ray_cast(reflect_ray, recurse);
	color = color_scale(color, specular_rs * specular_rs);
	return (color);
}

static t_color	specular_helper(t_quadrics *hit_obj, \
								const t_light *target_light, \
								t_ray reflect_ray)
{
	t_vec3	dir_to_light;
	t_ray	ray_to_light;
	float	specular;
	float	dist[2];

	dir_to_light = v3_sub(target_light->o, reflect_ray.org);
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = reflect_ray.org;
	specular = v3_dot(ray_to_light.dir, reflect_ray.dir);
	if (specular <= 0)
		return (rgb_color(0, 0, 0));
	dist[0] = get_intersect_distance(get_scene()->quads, NULL, ray_to_light);
	dist[1] = v3_l2norm(dir_to_light);
	debug_specular(NULL, &dist[0], &dist[1], NULL);
	specular = (hit_obj->spec_rs) * pow(specular, hit_obj->spec_ns);
	if (isnan(dist[0]) == FALSE && dist[0] < dist[1] + EPSILON)
		return (rgb_color(0, 0, 0));
	specular = fmax(0, v3_dot(v3_normalize(dir_to_light), reflect_ray.dir));
	specular = (hit_obj->spec_rs) * pow(specular, hit_obj->spec_ns);
	debug_specular(NULL, NULL, NULL, &specular);
	if (specular < EPSILON)
		return (rgb_color(0, 0, 0));
	return (light_specular(target_light, specular));
}

t_color	specular_light(t_quadrics *hit_obj, t_vec3 mirror_ray, \
						t_vec3 hit_point, int recurse)
{
	t_light	*light;
	t_color	color;
	t_color	color_temp;
	t_ray	reflect_ray;

	debug_specular(&recurse, NULL, NULL, NULL);
	color = rgb_color(0, 0, 0);
	reflect_ray.dir = mirror_ray;
	reflect_ray.org = hit_point;
	light = get_scene()->light;
	while (light)
	{
		debug_light(light);
		color_temp = specular_helper(hit_obj, light, reflect_ray);
		color = color_add(color, color_temp);
		color_temp = object_specular(reflect_ray, recurse, hit_obj->spec_rs);
		color = color_add(color, color_temp);
		light = light->next;
	}
	return (color);
}
