/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_equations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:12:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/31 21:46:33 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "quadrics.h"
#include "debug_msgs.h"

//(a)t^2 + (2b)t + (c) = 0
static t_sols	solve_quadratic_half_eq(float a, float b, float c)
{
	t_sols	sol;
	float	discriminant;

	sol = (t_sols){NAN, NAN};
	if (a == 0 && b != 0)
		sol.sol1 = -c / (2 * b);
	else if (a != 0)
	{
		if (a < 0)
		{
			a = -a;
			b = -b;
			c = -c;
		}
		discriminant = b * b - a * c;
		if (discriminant >= 0)
		{
			sol.sol1 = (-b - sqrtf(discriminant)) / a;
			sol.sol2 = (-b + sqrtf(discriminant)) / a;
		}
	}
	debug_solve_equation(NULL, &discriminant, &sol.sol1, &sol.sol2);
	return (sol);
}

static float	find_plane_intersection(const t_quadrics *Q, const t_ray *R)
{
	float		dist;
	t_vec3		obj_org;
	const float	cos = v3_dot(R->dir, Q->dir);

	obj_org = v3_sub(Q->org, R->org);
	if (cos == 0)
		dist = NAN;
	else
	{
		dist = v3_dot(obj_org, Q->dir) / cos;
		if (dist <= 0)
			dist = NAN;
	}
	debug_solve_equation(NULL, NULL, &dist, NULL);
	return (dist);
}

static int	check_z_range(const t_quadrics *Q, \
										const t_ray *R, \
										float sol)
{
	t_vec3	intersection;
	float	z_value;

	intersection = v3_sub(v3_add(v3_mul(R->dir, sol), R->org), Q->org);
	z_value = v3_dot(intersection, Q->dir);
	debug_z_range(Q->range_z, &sol, &z_value);
	return (z_value >= Q->range_z[0] - EPSILON \
			&& z_value <= Q->range_z[1] + EPSILON);
}

float	find_intersection(const t_quadrics *Q, const t_ray *R)
{
	t_sols	sols;
	t_vec4	ray_org;
	float	coefs[3];
	t_vec4	tmp;

	if (Q->type == Q_PLANE)
		return (find_plane_intersection(Q, R));
	ray_org = v4_sub(R->org, Q->org);
	ray_org.w = 1;
	debug_find_intersection(Q, R);
	tmp = make_v4(v4_dot(R->dir, Q->coefs.col1), v4_dot(R->dir, Q->coefs.col2), \
				v4_dot(R->dir, Q->coefs.col3), v4_dot(R->dir, Q->coefs.col4));
	coefs[0] = v4_dot(tmp, R->dir);
	coefs[1] = v4_dot(tmp, ray_org);
	coefs[2] = quadratic_form(ray_org, Q->coefs, ray_org);
	sols = solve_quadratic_half_eq(coefs[0], coefs[1], coefs[2]);
	if (sols.sol1 > EPSILON && isnan(sols.sol1) == FALSE)
		if ((check_z_range(Q, R, sols.sol1)))
			return (sols.sol1);
	if (sols.sol2 > EPSILON && isnan(sols.sol2) == FALSE)
		if ((check_z_range(Q, R, sols.sol2)))
			return (sols.sol2);
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
