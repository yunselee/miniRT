/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:09:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/10/28 11:22:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "vector3.h"
#include "quadrics.h"
#include "ray_cast.h"
#include "scene_editer.h"
#include <stdio.h>
#include "debug_msgs.h"

static t_vec3	get_mirror_ray(t_vec3 normal, t_vec3 ray)
{
	t_vec3	reflect_ray;
	t_vec3	temp;

	temp = v3_mul(normal, -2 * v3_dot(ray, normal));
	reflect_ray = v3_add(ray, temp);
	return (v3_normalize(reflect_ray));
}

static t_color	ambient_light(const t_quadrics *Q, \
								t_color amb_color, \
								float ra, \
								t_vec3 hit_point)
{
	t_color	c;
	t_color	obj_color;

	debug_ambient(NULL);
	ra = fmin(1.0, fmax(0, ra));
	obj_color = get_texture_color(Q, &(Q->textures[T_TEXTURE]), hit_point);
	obj_color = color_disruption(Q, hit_point, obj_color);
	c.red = round((float)obj_color.red * ((float)amb_color.red / 255));
	c.green = round((float)obj_color.green * ((float)amb_color.green / 255));
	c.blue = round((float)obj_color.blue * ((float)amb_color.blue / 255));
	c.alpha = 0;
	c = color_scale(c, ra);
	debug_ambient(Q);
	return (c);
}

static t_vec3	apply_normal_map(const t_quadrics *Q, \
								t_vec3 hit_point, \
								t_vec3 normal)
{
	t_color	color;
	t_vec3	bump_vec;
	t_vec3	local_uv[2];
	t_vec3	temp_normal[3];

	if ((Q->textures[T_NORMAL]).img.img == NULL)
		return (normal);
	color = get_texture_color(Q, &Q->textures[T_NORMAL], hit_point);
	bump_vec = make_v3((float)color.red, (float)color.green, (float)color.blue);
	bump_vec = v3_mul(bump_vec, (float)2 / 255);
	bump_vec = v3_sub(bump_vec, make_v3(1, 1, 1));
	local_uv[0] = v3_normalize(v3_crs(Q->dir, normal));
	if (v3_isnull(local_uv[0]) == TRUE)
		local_uv[0] = Q->tan;
	local_uv[1] = v3_normalize(v3_crs(normal, local_uv[0]));
	temp_normal[0] = v3_mul(local_uv[0], bump_vec.x);
	temp_normal[1] = v3_mul(local_uv[1], bump_vec.y);
	temp_normal[2] = v3_mul(normal, bump_vec.z);
	normal = v3_add(temp_normal[0], temp_normal[1]);
	normal = v3_normalize(v3_add(normal, temp_normal[2]));
	return (normal);
}

static t_arg	init(t_quadrics *Q, t_vec3 hit_p, t_vec3 normal, t_vec3 mirray)
{
	t_arg	a;

	a.h_ob = Q;
	a.normal = normal;
	a.hit_point = hit_p;
	a.mirror_ray = mirray;
	return (a);
}

t_color	phong_reflection(t_quadrics *Q, \
						t_vec3 hit_point, \
						t_vec3 view_point, \
						int recurse)
{
	const t_scene	*scene = get_scene();
	t_vec3			normal;
	t_vec3			mirror_ray;
	t_color			color[3];
	t_arg			arg;

	if (get_scene_editer()->edit != FALSE)
		return (ambient_light(Q, scene->ambient_color, \
								0.8, hit_point));
	normal = quad_normal_vector(Q, hit_point, view_point);
	hit_point = v3_add(hit_point, v3_mul(normal, EPSILON));
	debug_phong_reflection(&normal, &hit_point);
	normal = apply_normal_map(Q, hit_point, normal);
	color[0] = ambient_light(Q, \
								scene->ambient_color, \
								scene->ambient_ratio, \
								hit_point);
	debug_color(&color[0]);
	debug_color(&color[1]);
	mirror_ray = get_mirror_ray(normal, v3_sub(hit_point, view_point));
	arg = init(Q, hit_point, normal, mirror_ray);
	color[1] = diffuse_specular(&arg, recurse);
	return (color_add(color[0], color[1]));
}
