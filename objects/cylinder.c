/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:11:12 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/07 17:34:39 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "ray_cast.h"
#include "libft.h"
#include "objects.h"

double	solve_quadratic_equation(double a, double b, double c);

static double	above_cylinder(t_ray ray, const t_obj_base *obj)
{
	t_vec3	center;
	t_vec3	intersection;
	double	dist;

	center = v3_sub(obj->o, ray.org);
	center = v3_add(center, v3_mul(obj->n, obj->h));
	if (v3_dot(ray.dir, obj->n) == 0)
		return (NAN);
	dist = v3_dot(center, obj->n) / v3_dot(ray.dir, obj->n);
	if (dist <= 0)
		return (NAN);
	intersection = v3_mul(ray.dir, dist);
	if (v3_l2norm(v3_sub(intersection, center)) > obj->r)
		return (NAN);
	return (v3_l2norm(intersection));
}

static double	below_cylinder(t_ray ray, const t_obj_base *obj)
{
	const t_vec3	center = v3_sub(obj->o, ray.org);
	const double	dist = v3_dot(center, obj->n) / v3_dot(ray.dir, obj->n);
	const t_vec3	intersection = v3_mul(ray.dir, dist);

	if (v3_dot(ray.dir, obj->n) == 0)
		return (NAN);
	if (dist <= 0)
		return (NAN);
	if (v3_l2norm(v3_sub(intersection, center)) > obj->r)
		return (NAN);
	return (v3_l2norm(intersection));
}

static double	outside_cylinder(t_ray ray, const t_obj_base *obj)
{
	const t_vec3	obj_org = v3_sub(obj->o, ray.org);
	const t_vec3	ray_proj = v3_normalize(v3_crs(obj->n, v3_crs(ray.dir, obj->n)));
	const t_vec3	org_proj  = v3_crs(obj->n, v3_crs(obj_org, obj->n));
	double	height;
	double		distance ;
	
	distance = solve_quadratic_equation(v3_dot(ray_proj, ray_proj), \
					-2 * v3_dot(org_proj, ray_proj), \
					v3_dot(org_proj, org_proj) - pow(obj->r, 2));;
	if (distance == NAN)
		return (NAN);
	distance /= v3_dot(ray.dir, ray_proj);
	height = v3_dot(v3_sub(v3_mul(ray.dir, distance), obj_org), obj->n);
	if (height == 0 || height == obj->h)
		return (NAN);
	else if (height < 0)
		return (below_cylinder(ray, obj));
	else if (height > obj->h)
		return (above_cylinder(ray, obj));
	return (distance);
}


static double	obj_interstion(t_ray ray, const t_obj_base *obj)
{
	const t_vec3	obj_org = v3_sub(obj->o, ray.org);
	const t_vec3	cam_from_cy = v3_sub(ray.dir, obj_org);
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
static t_vec3	obj_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
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
	printf("\tradius : %3.4f\n", obj->r);
	printf("\theight : %3.4f\n", obj->h);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n\n", red, green, blue);
}



struct objs_vtable_ *get_cylinder()
{

	static struct objs_vtable_ cylinder[] = { { obj_interstion, obj_get_normal_vector, obj_print_info} };

	return cylinder;
}
