/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:11:12 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:15:41 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "ray_cast.h"
#include "libft.h"

static double	above_cylinder_inside(t_vec3 ray, \
									t_object_base *obj, \
									unsigned int *pcolor, \
									t_vec3 offset)
{
	t_vec3	center;
	t_vec3	intersection;
	double	dist;

	center = vec3_subtract(obj->org, offset);
	center = vec3_add(center, vec3_scale(obj->normal, obj->height));
	if (vec3_dot(ray, obj->normal) == 0)
		return (NAN);
	dist = vec3_dot(center, obj->normal) / vec3_dot(ray, obj->normal);
	if (dist <= 0)
		return (NAN);
	intersection = vec3_scale(ray, dist);
	if (vec3_l2norm(vec3_subtract(intersection, center)) > obj->radius)
		return (NAN);
	*pcolor = color_to_hex(obj->color);
	return (vec3_l2norm(intersection));
}

static double	below_cylinder_inside(t_vec3 ray, \
									t_object_base *obj, \
									unsigned int *pcolor, \
								t_vec3 offset)
{
	t_vec3	center;
	t_vec3	intersection;
	double	dist;

	center = vec3_subtract(obj->org, offset);
	if (vec3_dot(ray, obj->normal) == 0)
		return (NAN);
	dist = vec3_dot(center, obj->normal) / vec3_dot(ray, obj->normal);
	if (dist <= 0)
		return (NAN);
	intersection = vec3_scale(ray, dist);
	if (vec3_l2norm(vec3_subtract(intersection, center)) > obj->radius)
		return (NAN);
	*pcolor = color_to_hex(obj->color);
	return (vec3_l2norm(intersection));
}

static double	solve_quadratic_equation(double a, double b, double c)
{
	double	solution;
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		solution = -1;
	else if (discriminant == 0)
		solution = -b;
	else
	{
		solution = -b - sqrt(discriminant);
		if (solution <= 0)
			solution = -b + sqrt(discriminant);
	}
	if (solution <= 0)
		return (NAN);
	return (solution / (2 * a));
}

static double	outside_cylinder(t_vec3 ray, \
								t_object_base *obj, \
								unsigned int *pcolor, \
								t_vec3 offset)
{
	double	distance;
	double	height;
	t_vec3	intersection;
	t_vec3	ray_proj;
	t_vec3	org_proj;
	t_vec3	obj_org;
	
	obj_org = vec3_subtract(obj->org, offset);
	ray_proj = vec3_normalize(vec3_cross(obj->normal, \
							vec3_cross(ray, obj->normal)));
	org_proj = vec3_cross(obj->normal, vec3_cross(obj_org, obj->normal));
	distance = solve_quadratic_equation(vec3_dot(ray_proj, ray_proj), \
					-2 * vec3_dot(org_proj, ray_proj), \
					vec3_dot(org_proj, org_proj) - pow(obj->radius, 2));
	if (distance == NAN)
		return (NAN);
	distance /= vec3_dot(ray, ray_proj);
	intersection = vec3_scale(ray, distance);
	height = vec3_dot(vec3_subtract(intersection, obj_org), obj->normal);
	if (height == 0 || height == obj->height)
		return (NAN);
	else if (height < 0)
		return (below_cylinder_inside(ray, obj, pcolor, offset));
	else if (height > obj->height)
		return (above_cylinder_inside(ray, obj, pcolor, offset));
	*pcolor = color_to_hex(obj->color);
	return (distance);
}

double	intersect_cylinder(t_vec3 ray, \
							t_object_base *obj, \
							unsigned int *pcolor, \
							t_vec3 offset)
{
	t_vec3	cam_from_cy;
	t_vec3	cam_from_cy_projection;
	double	dist;
	double	height;
	t_vec3	obj_org;

	obj_org = vec3_subtract(obj->org, offset);
	cam_from_cy = vec3_subtract(ray, obj_org);
	cam_from_cy_projection = vec3_cross(obj->normal, \
							vec3_cross(cam_from_cy, obj->normal));
	dist = vec3_l2norm(cam_from_cy_projection);
	if (dist == obj->radius)
		return (NAN);
	else if (dist < obj->radius)
	{
		height = vec3_dot(cam_from_cy, obj->normal);
		if (height == 0 || height == obj->height)
			return (NAN);
		else if (height < 0)
			return (below_cylinder_inside(ray, obj, pcolor, offset));
		else if (height > obj->height)
			return (above_cylinder_inside(ray, obj, pcolor, offset));
		else if (is_nullvec3(vec3_cross(ray, obj->normal)) == TRUE)
		{
			if (vec3_dot(ray, obj->normal) > 0)
				return (above_cylinder_inside(ray, obj, pcolor, offset));
			return (below_cylinder_inside(ray, obj, pcolor, offset));
		}
	}
	return (outside_cylinder(ray, obj, pcolor, offset));
}
