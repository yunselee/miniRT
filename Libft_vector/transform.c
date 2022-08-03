/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 04:53:04 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:27:39 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include <math.h>

t_vec3	transform_by_mat33(t_mat33 A, t_vec3 x)
{
	t_vec3	y;
	t_mat33	t;

	t = mat33_trans(A);
	y.x = v3_dot(t.r1, x);
	y.y = v3_dot(t.r2, x);
	y.z = v3_dot(t.r3, x);
	return (y);
}

t_vec3	rotate_vec3_rad(t_vec3 axis, double rad, t_vec3 x)
{
	t_vec3	k;
	t_quat	q;
	t_quat	v;
	t_quat	q_conj;

	k = v3_normalize(axis);
	k = v3_mul(k, sin(rad / 2));
	q = quat_by_vector(cos(rad / 2), k);
	q_conj = quat_conjugate(q);
	v = quat_by_vector(0, x);
	v = quat_mul(q, v);
	v = quat_mul(v, q_conj);
	return (v.k);
}

t_vec3	rotate_vec3_deg(t_vec3 axis, double deg, t_vec3 x)
{
	return (rotate_vec3_rad(axis, M_PI / 180 * deg, x));
}
