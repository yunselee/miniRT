/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:11:12 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 18:31:52 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "ray_cast.h"
#include "libft.h"
#include "objects.h"

double	solve_quadratic_equation(double a, double b, double c);

static double	above_cylinder(t_vec3 ray, t_obj_base *obj, \
								unsigned int *pcolor, t_vec3 offset)
{
	t_vec3	center;
	t_vec3	intersection;
	double	dist;

	center = v3_sub(obj->o, offset);
	center = v3_add(center, v3_mul(obj->n, obj->h));
	if (v3_dot(ray, obj->n) == 0)
		return (NAN);
	dist = v3_dot(center, obj->n) / v3_dot(ray, obj->n);
	if (dist <= 0)
		return (NAN);
	intersection = v3_mul(ray, dist);
	if (v3_l2norm(v3_sub(intersection, center)) > obj->r)
		return (NAN);
	*pcolor = color_to_hex(obj->color);
	return (v3_l2norm(intersection));
}

static double	below_cylinder(t_vec3 ray, t_obj_base *obj, \
								unsigned int *pcolor, t_vec3 offset)
{
	const t_vec3	center = v3_sub(obj->o, offset);
	const double	dist = v3_dot(center, obj->n) / v3_dot(ray, obj->n);
	const t_vec3	intersection = v3_mul(ray, dist);

	if (v3_dot(ray, obj->n) == 0)
		return (NAN);
	if (dist <= 0)
		return (NAN);
	if (v3_l2norm(v3_sub(intersection, center)) > obj->r)
		return (NAN);
	*pcolor = color_to_hex(obj->color);
	return (v3_l2norm(intersection));
}

static double	outside_cylinder(t_vec3 ray, t_obj_base *obj, \
								unsigned int *pcolor, t_vec3 offset)
{
	const t_vec3	obj_org = v3_sub(obj->o, offset);
	const t_vec3	ray_proj = v3_normalize(v3_crs(obj->n, v3_crs(ray, obj->n)));
	const t_vec3	org_proj  = v3_crs(obj->n, v3_crs(obj_org, obj->n));
	double	height;
	double		distance ;
	
	distance = solve_quadratic_equation(v3_dot(ray_proj, ray_proj), \
					-2 * v3_dot(org_proj, ray_proj), \
					v3_dot(org_proj, org_proj) - pow(obj->r, 2));;
	if (distance == NAN)
		return (NAN);
	distance /= v3_dot(ray, ray_proj);
	height = v3_dot(v3_sub(v3_mul(ray, distance), obj_org), obj->n);
	if (height == 0 || height == obj->h)
		return (NAN);
	else if (height < 0)
		return (below_cylinder(ray, obj, pcolor, offset));
	else if (height > obj->h)
		return (above_cylinder(ray, obj, pcolor, offset));
	*pcolor = color_to_hex(obj->color);
	return (distance);
}


static double	obj_interstion(t_vec3 ray, t_obj_base *obj, \
							unsigned int *pcolor, t_vec3 offset)
{
	const t_vec3	obj_org = v3_sub(obj->o, offset);
	const t_vec3	cam_from_cy = v3_sub(ray, obj_org);
	const t_vec3 cam_from_cy_proj = v3_crs(obj->n, v3_crs(cam_from_cy, obj->n));
	const double	dist = v3_l2norm(cam_from_cy_proj);
	const double	height = v3_dot(cam_from_cy, obj->n);

	if (dist == obj->r)
		return (NAN);
	else if (dist < obj->r)
	{
		if (height == 0 || height == obj->h)
			return (NAN);
		else if (height < 0)
			return (below_cylinder(ray, obj, pcolor, offset));
		else if (height > obj->h)
			return (above_cylinder(ray, obj, pcolor, offset));
	}
	return (outside_cylinder(ray, obj, pcolor, offset));
}

/*
o_to_p : org_of_object to intersect point
cam_to_p : cam_position to intersect point
o_n : normal vector of object
*/
static t_vec3	obj_get_normal_vector(t_obj_base *obj, t_vec3 point, \
									t_vec3 cam_pos)
{
	const t_vec3	o_n  = obj->n;;
	const t_vec3	cam_to_p  = v3_sub(point, cam_pos);
	t_vec3	normal;
	t_vec3	o_to_p;

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

struct objs_vtable_ *get_cylinder()
{
	static struct objs_vtable_ cylinder[] = { { obj_interstion, obj_get_normal_vector } };

	return cylinder;
}
