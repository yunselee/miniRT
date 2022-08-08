/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_ect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:58:22 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/08 19:44:51 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "ray_cast.h"
#include "libft.h"
#include "objects.h"

// discriminant : 이차방정식의 판별식
double	solve_quadratic_equation(double a, double b, double c)
{
	double	solution;
	double	discriminant;

	if (a < 0)
	{
		a = -a;
		b = -b;
		c = -c;
	}
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

double	above_cylinder(t_ray ray, const t_obj_base *obj)
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

double	below_cylinder(t_ray ray, const t_obj_base *obj)
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

double	outside_cylinder(t_ray ray, const t_obj_base *obj)
{
	const t_vec3	obj_org = v3_sub(obj->o, ray.org);
	const t_vec3	ray_proj = v3_normalize(\
								v3_crs(obj->n, v3_crs(ray.dir, obj->n)));
	const t_vec3	org_proj = v3_crs(obj->n, v3_crs(obj_org, obj->n));
	double			height;
	double			distance ;

	distance = solve_quadratic_equation(v3_dot(ray_proj, ray_proj), \
					-2 * v3_dot(org_proj, ray_proj), \
					v3_dot(org_proj, org_proj) - pow(obj->r, 2));
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
