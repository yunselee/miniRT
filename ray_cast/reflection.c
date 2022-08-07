/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:09:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 21:23:36 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"

static t_color	ambient_light(t_color obj_color, t_color amb_color, double ra)
{
	t_color	c;

	if (ra < 0)
		ra = 0;
	else if (ra > 1)
		ra = 1;
	c.red = round((double)obj_color.red * ((double)amb_color.red / 255));
	c.green = round((double)obj_color.green * ((double)amb_color.green / 255));
	c.blue = round((double)obj_color.blue * ((double)amb_color.blue / 255));
	c = color_scale(c, ra);
	return (c);
}

t_color	phong_reflection(t_mlx *mlx, \
						t_obj_base *hit_obj, \
						t_vec3 intersection, \
						t_vec3 view_point)
{
	t_vec3	normal;
	t_vec3	mirror_reflect;
	t_color	radiosity[3];

	if (mlx->edit != FALSE)
	{
		radiosity[0] = ambient_light(hit_obj->color, \
										mlx->scene->ambient_color, \
										0.8);
		return (radiosity[0]);
	}
	normal = get_normal_vector(hit_obj, intersection, view_point);
	intersection = v3_add(intersection, v3_mul(normal, EPSILON));
	radiosity[0] = ambient_light(hit_obj->color, \
									mlx->scene->ambient_color, \
									mlx->scene->ambient_ratio);
	radiosity[1] = diffuse_light(mlx->scene, hit_obj, normal, intersection);
	mirror_reflect = v3_sub(intersection, view_point);
	mirror_reflect = v3_add(mirror_reflect, \
						v3_mul(normal, -2 * v3_dot(normal, mirror_reflect)));
	mirror_reflect = v3_normalize(mirror_reflect);
	radiosity[2] = specular_light(mlx->scene, mirror_reflect, intersection);
	return (color_add(color_add(radiosity[0], radiosity[1]), radiosity[2]));
}
