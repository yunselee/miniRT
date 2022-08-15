/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:09:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/15 15:50:50 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "vector3.h"
#include "quadrics.h"
#include "ray_cast.h"

static t_vec3	get_mirror_ray(t_vec3 normal, t_vec3 ray)
{
	t_vec3	reflect_ray;
	t_vec3	temp;

	temp = v3_mul(normal, -2 * v3_dot(ray, normal));
	reflect_ray = v3_add(ray, temp);
	return (v3_normalize(reflect_ray));
}

static t_color	ambient_light(const t_quadrics *hit_obj, \
								t_color amb_color, \
								float ra, \
								t_vec3 hit_point)
{
	t_color	c;
	t_color	obj_color;

	if (ra < 0)
		ra = 0;
	else if (ra > 1)
		ra = 1;
	obj_color = get_texture_color(hit_obj, &hit_obj->texture, hit_point);
	obj_color = color_disruption(hit_obj, hit_point, obj_color);
	c.red = round((float)obj_color.red * ((float)amb_color.red / 255));
	c.green = round((float)obj_color.green * ((float)amb_color.green / 255));
	c.blue = round((float)obj_color.blue * ((float)amb_color.blue / 255));
	c = color_scale(c, ra);
	return (c);
}

static t_vec3	apply_bump_map(const t_quadrics *Q, t_vec3 hit_point, t_vec3 normal)
{
	t_color	color;
	t_vec3	bump_vec;
	t_vec3	temp_uv[2];
	t_vec3	temp_normal[3];

	if (Q->bumpmap.img.img == NULL)
		return (normal);
	color = get_texture_color(Q, &Q->bumpmap, hit_point);
	bump_vec = make_v3((float)color.red, (float)color.green, (float)color.blue);
	bump_vec = v3_mul(bump_vec, (float)2 / 255);
	bump_vec = v3_sub(bump_vec, make_v3(1, 1, 1));
	temp_uv[0] = v3_normalize(v3_crs(Q->dir, normal));
	if (v3_isnull(temp_uv[0]) == TRUE)
	// if (Q->type == Q_PLANE)
		temp_uv[0] = Q->tan;
	temp_uv[1] = v3_normalize(v3_crs(normal, temp_uv[0]));
	temp_normal[0] = v3_mul(temp_uv[0], bump_vec.x);
	temp_normal[1] = v3_mul(temp_uv[1], bump_vec.y);
	temp_normal[2] = v3_mul(normal, bump_vec.z);
	normal = v3_add(temp_normal[0], temp_normal[1]);
	normal = v3_normalize(v3_add(normal, temp_normal[2]));
	return (normal);
}

t_color	phong_reflection(t_mlx *mlx, \
						t_quadrics *hit_obj, \
						t_vec3 hit_point, \
						t_vec3 view_point)
{
	const t_scene *scene = get_scene();
	t_vec3	normal;
	t_vec3	mirror_ray;
	t_color	radiosity[3];

	if (mlx->edit != FALSE)
		return (ambient_light(hit_obj, scene->ambient_color, \
								0.8, hit_point));
	normal = quad_normal_vector(hit_obj, hit_point, view_point);
	hit_point = v3_add(hit_point, v3_mul(normal, EPSILON));
	normal = apply_bump_map(hit_obj, hit_point, normal);
	radiosity[0] = ambient_light(hit_obj, \
								scene->ambient_color, \
								scene->ambient_ratio, \
								hit_point);
	radiosity[1] = diffuse_light(scene, hit_obj, normal, hit_point);
	mirror_ray = get_mirror_ray(normal, v3_sub(hit_point, view_point));
	radiosity[2] = specular_light(scene, hit_obj, mirror_ray, hit_point);
	return (color_add(color_add(radiosity[0], radiosity[1]), radiosity[2]));
}
