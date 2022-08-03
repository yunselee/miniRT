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
	t_vec3	center;
	t_vec3	intersection;
	double	dist;

	center = v3_sub(obj->o, offset);
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

static double	outside_cylinder(t_vec3 ray, t_obj_base *obj, \
								unsigned int *pcolor, t_vec3 offset)
{
	double	distance;
	double	height;
	t_vec3	ray_proj;
	t_vec3	org_proj;
	t_vec3	obj_org;

	obj_org = v3_sub(obj->o, offset);
	ray_proj = v3_normalize(v3_crs(obj->n, \
							v3_crs(ray, obj->n)));
	org_proj = v3_crs(obj->n, v3_crs(obj_org, obj->n));
	distance = solve_quadratic_equation(v3_dot(ray_proj, ray_proj), \
					-2 * v3_dot(org_proj, ray_proj), \
					v3_dot(org_proj, org_proj) - pow(obj->r, 2));
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

double	intersect_cylinder(t_vec3 ray, t_obj_base *obj, \
							unsigned int *pcolor, t_vec3 offset)
{
	t_vec3	cam_from_cy;
	t_vec3	cam_from_cy_proj;
	double	dist;
	double	height;
	t_vec3	obj_org;

	obj_org = v3_sub(obj->o, offset);
	cam_from_cy = v3_sub(ray, obj_org);
	cam_from_cy_proj = v3_crs(obj->n, v3_crs(cam_from_cy, obj->n));
	dist = v3_l2norm(cam_from_cy_proj);
	if (dist == obj->r)
		return (NAN);
	else if (dist < obj->r)
	{
		height = v3_dot(cam_from_cy, obj->n);
		if (height == 0 || height == obj->h)
			return (NAN);
		else if (height < 0)
			return (below_cylinder(ray, obj, pcolor, offset));
		else if (height > obj->h)
			return (above_cylinder(ray, obj, pcolor, offset));
	}
	return (outside_cylinder(ray, obj, pcolor, offset));
}
