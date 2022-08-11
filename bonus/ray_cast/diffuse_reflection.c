/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_reflection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:22:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 21:06:33 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"


#include <stdio.h>
static float	diffuse_helper(t_quadrics *objlst, \
							t_light *target_light, \
							t_vec3 normal, \
							t_vec3 intersection)
{
	t_quadrics	*target_obj;
	t_vec3		dir_to_light;
	float		dist[2];
	float		diffuse;
	t_ray		ray_to_light;

	dist[0] = INFINITY;
	// printf("\ttarget_light->o : %f %f %f %f\n", target_light->o.x, target_light->o.y, target_light->o.z, target_light->o.w);
	dir_to_light = v3_sub(target_light->o, intersection);
	// printf("\tdir_to_light : %f %f %f %f\n", dir_to_light.x, dir_to_light.y, dir_to_light.z, dir_to_light.w);
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = intersection;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = find_intersection(target_obj, &ray_to_light);
		// printf("\tdist : %f\n", dist[1]);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
			dist[0] = dist[1];
		target_obj = target_obj->next;
	}
	// printf("dir_to_light : %f %f %f\n", ray_to_light.dir.x, ray_to_light.dir.y, ray_to_light.dir.z);
	// printf("normal : %f %f %f\n", normal.x, normal.y, normal.z);
	// printf("dot : %f\n", v3_dot(ray_to_light.dir, normal));
	if (isnan(dist[0]) == FALSE && dist[0] < v3_l2norm(dir_to_light) + EPSILON)
		return (0);
	diffuse = fmax(0, v3_dot(v3_normalize(dir_to_light), normal));
	diffuse *= target_light->bright;
	return (diffuse);
}

t_color	diffuse_light(t_scene *scene, \
					t_quadrics *hit_obj, \
					t_vec3 normal, t_vec3 \
					intersection)
{
	t_light	*light;
	t_color	color;
	t_color	color_temp;
	float	diffuse;

	// printf("\033[0;36m");
	// printf("diffuse start\n");
	intersection = v3_add(intersection, v3_mul(normal, EPSILON));
	color = rgb_color(0, 0, 0);
	light = scene->light;
	while (light != NULL)
	{
		diffuse = diffuse_helper(scene->quads, light, normal, intersection);
		if (diffuse > EPSILON)
		{
			color_temp.red = roundf((float)light->color.red / 255 \
									* hit_obj->color.red);
			color_temp.green = roundf((float)light->color.green / 255 \
									* hit_obj->color.green);
			color_temp.blue = roundf((float)light->color.blue / 255 \
									* hit_obj->color.blue);
			color_temp = color_scale(color_temp, diffuse * (1 - hit_obj->spec_rs));
			color = color_add(color, color_temp);
		}
		light = light->next;
	}
	// printf("diffuse end\033[0m\n");
	return (color);
}
