/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_reflection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:22:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/22 17:02:17 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include <assert.h>
#include <stdio.h>
#include "print_info.h"
#include "debug_msgs.h"

static float	diffuse_helper(t_quadrics *objlst, \
							t_light *target_light, \
							t_vec3 normal, \
							t_vec3 hit_point)
{
	t_vec3		dir_to_light;
	t_ray		ray_to_light;
	float		diffuse;
	float		distance[2];

	debug_light(target_light);
	dir_to_light = v3_sub(target_light->o, hit_point);
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = hit_point;
	diffuse = v3_dot(ray_to_light.dir, normal);
	if (diffuse <= 0)
		return (0);
	distance[0] = get_intersect_distance(objlst, NULL, ray_to_light);
	distance[1] = v3_l2norm(dir_to_light);
	debug_diffuse(&distance[0], &distance[1], NULL);
	if (isnan(distance[0]) == FALSE && distance[0] < distance[1] + EPSILON)
		return (0);
	diffuse *= target_light->bright;
	debug_diffuse(NULL, NULL, &diffuse);
	return (diffuse);
}

t_color	diffuse_light(const t_scene *scene, \
					t_quadrics *Q, \
					t_vec3 normal, \
					t_vec3 hit_point)
{
	const t_color	obj_clr = color_disruption(Q, hit_point, \
				get_texture_color(Q, &(Q->textures[T_TEXTURE]), hit_point));
	t_light			*light;
	t_color			color;
	t_color			clr_tmp;
	float			diffuse;

	hit_point = v3_add(hit_point, v3_mul(normal, EPSILON));
	color = rgb_color(0, 0, 0);
	debug_diffuse(NULL, NULL, NULL);
	light = scene->light;
	while (light != NULL)
	{
		diffuse = diffuse_helper(scene->quads, light, normal, hit_point);
		if (diffuse > 0)
		{
			clr_tmp.red = ((float)light->color.red / 255 * obj_clr.red);
			clr_tmp.green = ((float)light->color.green / 255 * obj_clr.green);
			clr_tmp.blue = ((float)light->color.blue / 255 * obj_clr.blue);
			clr_tmp = color_scale(clr_tmp, diffuse * (1 - Q->spec_rs));
			color = color_add(color, clr_tmp);
		}
		light = light->next;
	}
	return (color);
}
