/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:11:12 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/10 22:54:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "ray_cast.h"
#include "libft.h"
#include "objects.h"

double	above_cylinder(t_ray ray, const t_obj_base *obj);
double	below_cylinder(t_ray ray, const t_obj_base *obj);
double	outside_cylinder(t_ray ray, const t_obj_base *obj);

static double	obj_interstion(t_ray ray, const t_obj_base *obj)
{
	const t_vec3	obj_org = v3_sub(obj->o, ray.org);
	const t_vec3	cam_from_cy = v3_sub(ray.dir, obj_org);
	const t_vec3	cam_from_cy_proj = v3_crs(obj->n, \
										v3_crs(cam_from_cy, obj->n));
	const double	dist = v3_l2norm(cam_from_cy_proj);
	const double	height = v3_dot(cam_from_cy, obj->n);

	if (dist == obj->r)
		return (NAN);
	else if (dist < obj->r)
	{
		if (height == 0 || height == obj->h)
			return (NAN);
		else if (height < 0)
			return (below_cylinder(ray, obj));
		else if (height > obj->h)
			return (above_cylinder(ray, obj));
	}
	return (outside_cylinder(ray, obj));
}

/*
o_to_p : org_of_object to intersect point
cam_to_p : cam_position to intersect point
o_n : normal vector of object
*/
t_vec3	cylinder_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
									t_vec3 cam_pos)
{
	const t_vec3	o_n = obj->n;
	const t_vec3	cam_to_p = v3_sub(point, cam_pos);
	t_vec3			normal;
	t_vec3			o_to_p;

	o_to_p = v3_sub(point, obj->o);
	if (v3_dot(o_to_p, o_n) <= EPSILON && v3_dot(o_to_p, o_n) >= -EPSILON)
	{
		if (v3_dot(o_n, cam_to_p) > 0)
			return (v3_mul(o_n, -1));
		return (o_n);
	}
	o_to_p = v3_sub(point, v3_add(obj->o, v3_mul(o_n, obj->h)));
	if (v3_dot(o_to_p, o_n) <= EPSILON && v3_dot(o_to_p, o_n) >= -EPSILON)
	{
		if (v3_dot(o_n, cam_to_p) > 0)
			return (v3_mul(o_n, -1));
		return (o_n);
	}
	normal = v3_normalize(v3_crs(o_n, v3_crs(o_to_p, o_n)));
	if (v3_l2norm(v3_crs(o_n, v3_crs((v3_sub(cam_pos, obj->o)), o_n))) < obj->r)
		normal = v3_mul(normal, -1);
	return (normal);
}

static void	obj_print_info(const t_obj_base *obj)
{
	int	red;
	int	green;
	int	blue;

	red = obj->color.red;
	green = obj->color.green;
	blue = obj->color.blue;
	printf("\ttype : CYLINDER\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->o.x \
											, obj->o.y \
											, obj->o.z);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", obj->n.x \
												, obj->n.y \
												, obj->n.z);
	printf("\ttangential : [%3.4f, %3.4f, %3.4f]\n", obj->tangential.x \
												, obj->tangential.y \
												, obj->tangential.z);
	printf("\tradius : %3.4f\n", obj->r);
	printf("\theight : %3.4f\n", obj->h);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n", red, green, blue);
	printf("\tspecular factors : Rs : %.2f alpha : %d\n\n", obj->rs, obj->ns);
}

struct s_obj_vtable_	*get_cylinder(void)
{
	static struct s_obj_vtable_	cylinder[5];

	cylinder->obj_interstion = obj_interstion;
	cylinder->obj_print_info = obj_print_info;
	return (cylinder);
}
