/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_equations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:12:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 19:24:30 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quadrics.h"
#include <math.h>
#include <stdio.h>

//(a)t^2 + (2b)t + (c) = 0
static t_sols	solve_quadratic_half_eq(double a, double b, double c)
{
	t_sols	sol;
	double	discriminant;

	sol.sol2 = NAN;
	sol.sol1 = NAN;
	if (a < EPSILON && a > -EPSILON)
	{
		if (b != 0)
			sol.sol1 = -c / (2 * b);
	}
	else
	{
		if (a < 0)
		{
			a = -a;
			b = -b;
			c = -c;
		}
		discriminant = b * b - a * c;
		if (discriminant >= 0)
			sol.sol1 = (-b - sqrt(discriminant)) / a;
		if (discriminant > 0)
			sol.sol2 = (-b + sqrt(discriminant)) / a;
	}
	return (sol);
}

static double	find_plane_intersection(const t_quadrics *Q, const t_ray *R)
{
	double	dist;
	t_vec3	obj_org;

	obj_org = v3_sub(Q->org, R->org);
	if (v3_dot(R->dir, Q->dir) == 0)
		return (NAN);
	dist = v3_dot(obj_org, Q->dir) / v3_dot(R->dir, Q->dir);
	if (dist < EPSILON)
		return (NAN);
	return (dist);
}

static double	z_range_check_or_nan(const t_quadrics *Q, \
										const t_ray *R, \
										double sol)
{
	t_vec3	intersection;

	intersection = v3_sub(v3_add(v3_mul(R->dir, sol), R->org), Q->org);
	if (v3_dot(intersection, Q->dir) >= Q->range_z[0] - EPSILON \
			&& v3_dot(intersection, Q->dir) <= Q->range_z[1] + EPSILON)
		return (sol);
	return (NAN);
}

double	find_intersection(const t_quadrics *Q, const t_ray *R)
{
	t_sols	sols;
	t_vec4	ray_org;
	double	coefs[3];

	ray_org = v4_sub(make_v4(R->org.x, R->org.y, R->org.z, 1), Q->org);
	ray_org.w = 1;
	if (Q->type == Q_PLANE)
		return (find_plane_intersection(Q, R));
	coefs[0] = quadratic_form(R->dir, Q->coefs, R->dir);
	coefs[1] = quadratic_form(R->dir, Q->coefs, ray_org);
	coefs[2] = quadratic_form(ray_org, Q->coefs, ray_org);
	sols = solve_quadratic_half_eq(coefs[0], coefs[1], coefs[2]);
	if (sols.sol1 > EPSILON && isnan(sols.sol1) == FALSE)
	{
		if (isnan(z_range_check_or_nan(Q, R, sols.sol1)) == FALSE)
			return (sols.sol1);
	}
	if (sols.sol2 > EPSILON && isnan(sols.sol2) == FALSE)
	{
		if (isnan(z_range_check_or_nan(Q, R, sols.sol2)) == FALSE)
			return (sols.sol2);
	}
	return (NAN);
}

t_vec3	quad_normal_vector(const t_quadrics *Q, t_vec4 point, t_vec4 viewpoint)
{
	t_vec3	normal;
	t_vec3	point_from_obj;

	if (Q->type == Q_PLANE)
		normal = Q->dir;
	else
	{
		point_from_obj = v3_sub(point, Q->org);
		point_from_obj.w = 1;
		normal.x = v4_dot(Q->coefs.col1, point_from_obj);
		normal.y = v4_dot(Q->coefs.col2, point_from_obj);
		normal.z = v4_dot(Q->coefs.col3, point_from_obj);
		normal.w = 0;
		normal = v3_normalize(normal);
	}
	if (v3_dot(v3_sub(point, viewpoint), normal) > 0)
		normal = v3_mul(normal, -1);
	return (normal);
}
