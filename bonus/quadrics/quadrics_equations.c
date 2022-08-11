/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_equations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:12:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 22:08:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quadrics.h"
#include <math.h>
#include <stdio.h>

// static void print_mat44(const t_mat44 *M)
// {
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.x, M->col2.x, M->col3.x, M->col4.x);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.y, M->col2.y, M->col3.y, M->col4.y);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.z, M->col2.z, M->col3.z, M->col4.z);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.w, M->col2.w, M->col3.w, M->col4.w);
// }

//(a)t^2 + (2b)t + (c) = 0
static t_sols	solve_quadratic_half_eq(float a, float b, float c)
{
	t_sols	sol;
	float	discriminant;

	sol.sol2 = NAN;
	if (a < EPSILON && a > -EPSILON)
	{
		// printf("  A = 0\n");
		if (b == 0)
			sol.sol1 = NAN;
		else
			sol.sol1 = -c / (2 * b);
	}
	else
	{
		discriminant = b * b - a * c;
		// printf("D = %f\n", discriminant);
		if (discriminant < 0)
			sol.sol1 = NAN;
		else if (discriminant >= 0)
			sol.sol1 = (-b - sqrtf(discriminant)) / a;
		if (discriminant > 0)
			sol.sol2 = (-b + sqrtf(discriminant)) / a;
	}
	return (sol);
}

static float	find_plane_intersection(const t_quadrics *Q, const t_ray *R)
{
	float	dist;
	t_vec3	obj_org;

	obj_org = v3_sub(Q->org, R->org);
	if (v3_dot(R->dir, Q->dir) == 0)
		return (NAN);
	dist = v3_dot(obj_org, Q->dir) / v3_dot(R->dir, Q->dir);
	if (dist <= 0)
		return (NAN);
	return (dist);
}

float	find_intersection(const t_quadrics *Q, const t_ray *R)
{
	t_sols	sols;
	t_vec4	ray_org;
	float	coefs[3];
	t_vec3	intersection;
	
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
		intersection = v3_sub(v3_add(v3_mul(R->dir, sols.sol1), R->org), Q->org);
		if (v3_dot(intersection, Q->dir) >= Q->range_z[0] - EPSILON\
			&& v3_dot(intersection, Q->dir) <= Q->range_z[1] + EPSILON)
			return (sols.sol1);
	}
	if (sols.sol2 > EPSILON && isnan(sols.sol2) == FALSE)
	{
		intersection = v3_sub(v3_add(v3_mul(R->dir, sols.sol2), R->org), Q->org);
		if (v3_dot(intersection, Q->dir) >= Q->range_z[0] -EPSILON \
			&& v3_dot(intersection, Q->dir) <= Q->range_z[1] +EPSILON)
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