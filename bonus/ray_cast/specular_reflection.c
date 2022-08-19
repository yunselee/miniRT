/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:20:20 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/19 13:05:47 by dkim2            ###   ########.fr       */
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

static t_color	specular_helper(t_quadrics *hit_obj, \
								const t_light *target_light, \
								t_vec3 mirror_ray, \
								t_vec3 hit_point)
{
	t_vec3	dir_to_light;
	t_ray	ray_to_light;
	float	specular;
	float	distance[2];

	dir_to_light = v3_sub(target_light->o, hit_point);
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = hit_point;
	distance[0] = get_intersect_distance(get_scene()->quads, NULL, ray_to_light);
	distance[1] = v3_l2norm(dir_to_light);
	specular = fmax(0, v3_dot(v3_normalize(dir_to_light), mirror_ray));
	specular = (hit_obj->spec_rs) * pow(specular, hit_obj->spec_ns);
	debug_specular(&distance[0], &distance[1], NULL);
	debug_specular(NULL, NULL, &specular);
	if (isnan(distance[0]) == FALSE && distance[0] < distance[1] + EPSILON)
		return (rgb_color(0, 0, 0));
	else if (specular < EPSILON)
		return (rgb_color(0, 0, 0));
	else
		return (light_specular(target_light, specular));
}

t_color	specular_light(const t_scene *scene, t_quadrics *hit_obj, \
						t_vec3 mirror_ray, t_vec3 hit_point)
{
	t_light	*light;
	t_color	color;
	t_color	color_temp;

	color = rgb_color(0, 0, 0);
	light = scene->light;
	debug_specular(NULL, NULL, NULL);
	while (light)
	{
		debug_light(light);
		color_temp = specular_helper(hit_obj, light, mirror_ray, hit_point);
		color = color_add(color, color_temp);
		light = light->next;
	}
	debug_color(&color);
	return (color);
}
