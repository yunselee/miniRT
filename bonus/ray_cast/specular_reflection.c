/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:20:20 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/17 21:17:46 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include "scene.h"
#include <assert.h>
#include <stdio.h>
#include "debug_msgs.h"

static float	specular_helper(t_quadrics *objlst, \
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
	distance[0] = get_intersect_distance(objlst, NULL, ray_to_light);
	distance[1] = v3_l2norm(dir_to_light);
	debug_specular(&distance[0], &distance[1], NULL);
	if (isnan(distance[0]) == FALSE && distance[0] < distance[1] + EPSILON)
		return (0);
	specular = fmax(0, v3_dot(v3_normalize(dir_to_light), mirror_ray));
	return (specular);
}

t_color	specular_light(const t_scene *scene, t_quadrics *hit_obj, \
						t_vec3 mirror_ray, t_vec3 hit_point)
{
	t_light	*light;
	t_color	color;
	t_color	color_temp;
	float	specular;

	color = rgb_color(0, 0, 0);
	light = scene->light;
	debug_specular(NULL, NULL, NULL);
	while (light)
	{
		debug_light(light);
		specular = specular_helper(scene->quads, light, mirror_ray, hit_point);
		specular = (hit_obj->spec_rs) * pow(specular, hit_obj->spec_ns);
		debug_specular(NULL, NULL, &specular);
		if (specular > EPSILON)
		{
			color_temp.red = roundf((float)light->color.red / 255 \
									* light->color.red);
			color_temp.green = roundf((float)light->color.green / 255 \
									* light->color.green);
			color_temp.blue = roundf((float)light->color.blue / 255 \
									* light->color.blue);
			color_temp.alpha = 0;
			color_temp = color_scale(color_temp, specular);
			color = color_add(color, color_temp);
		}
		light = light->next;
	}
	debug_color(&color);
	return (color);
}
