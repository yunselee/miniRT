/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:47:27 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:10:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ray_cast.h"


// discriminant : 이차방정식의 판별식
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

static double	intersect_plane(t_vec3 ray, \
								t_object_base *obj, \
								unsigned int *pcolor,\
								t_vec3 offset)
{
	double	dist;
	t_vec3	obj_org;

	obj_org = vec3_subtract(obj->org, offset);
	if (vec3_dot(ray, obj->normal) == 0)
		return (NAN);
	dist = vec3_dot(obj_org, obj->normal) / vec3_dot(ray, obj->normal);
	if (dist <= 0)
		return (NAN);
	*pcolor = color_to_hex(obj->color);
	return (dist);
}

static double	intersect_sphere(t_vec3 ray, \
								t_object_base *obj, \
								unsigned int *pcolor, \
								t_vec3 offset)
{
	double	distance;
	t_vec3	obj_org;

	obj_org = vec3_subtract(obj->org, offset);
	distance = solve_quadratic_equation(vec3_dot(ray, ray), \
					-2 * vec3_dot(obj_org, ray), \
					vec3_dot(obj_org, obj_org) - pow(obj->radius, 2));
	if (distance == NAN)
		return (NAN);
	*pcolor = color_to_hex(obj->color);
	return (distance);
}

double	object_intersect(t_vec3 ray, t_object_base *obj, unsigned int *pcolor,t_vec3 offset)
{
	if (obj->type == E_PLANE)
		return (intersect_plane(ray, obj, pcolor, offset));
	else if (obj->type == E_SPHERE)
		return (intersect_sphere(ray, obj, pcolor, offset));
	else if (obj->type == E_CYLINDER)
		return (intersect_cylinder(ray, obj, pcolor, offset));
	else
		return (NAN);
}
