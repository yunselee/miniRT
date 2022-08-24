/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_diffuse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:31:26 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/24 15:37:07 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include "scene.h"
#include <stdio.h>
#include "debug_msgs.h"

static t_color	object_specular(t_ray reflect_ray, \
								int recurse, \
								float specular_rs)
{
	t_color	color;

	color = single_ray_cast(reflect_ray, recurse);
	color = color_scale(color, specular_rs * specular_rs);
	return (color);
}

static void	zero_return(float *outDiffuse, float *outSpecular)
{
	*outSpecular = 0;
	*outDiffuse = 0;
}

static void	helper(
	const t_arg *a, \
	const t_light *target_light, \
	t_ray reflect_ray,
	float out[2])
{
	const t_vec3	p_to_l = v3_sub(target_light->o, reflect_ray.org);
	const float		len = v3_l2norm(p_to_l);
	const t_ray		ray_to_light = {reflect_ray.org, v4_mul(p_to_l, 1 / len)};
	float			distance;

	debug_light(target_light);
	out[0] = v3_dot(ray_to_light.dir, a->normal);
	out[1] = v3_dot(ray_to_light.dir, reflect_ray.dir);
	if (out[0] <= 0 && out[1] <= 0)
		zero_return(&out[0], &out[1]);
	distance = get_intersect_distance(get_scene()->quads, NULL, ray_to_light);
	debug_diffuse(&distance, &len, NULL);
	if (isnan(distance) == FALSE && distance < len + EPSILON)
		zero_return(&out[0], &out[1]);
	out[0] *= target_light->bright;
	out[1] = (a->h_ob->spec_rs) * pow(out[1], a->h_ob->spec_ns);
	debug_diffuse(NULL, NULL, &out[0]);
	if (out[0] < EPSILON)
		out[0] = 0;
	if (out[1] < EPSILON)
		out[1] = 0;
}

t_color	diffuse_specular(t_arg *a, int recurse)
{
	const t_color	oclr = color_disruption(a->h_ob, a->hit_point, \
	get_texture_color(a->h_ob, &(a->h_ob->textures[T_TEXTURE]), a->hit_point));
	const t_light	*light = get_scene()->light;
	const t_ray		reflect = {a->hit_point, a->mirror_ray};
	t_color			c;
	float			d[2];

	a->hit_point = v3_add(a->hit_point, v3_mul(a->normal, EPSILON));
	c = rgb_color(0, 0, 0);
	debug_diffuse(NULL, NULL, NULL);
	while (light != NULL)
	{
		debug_light(light);
		helper(a, light, reflect, d);
		if (d[0] > 0)
			c = color_add(c, color_dot(light->color, oclr, \
					d[0] * (1 - a->h_ob->spec_rs)));
		if (d[1] > 0)
			c = color_add(c, color_scale(light->color, d[1] * light->bright));
		c = color_add(c, object_specular(reflect, recurse, a->h_ob->spec_rs));
		light = light->next;
	}
	return (c);
}
