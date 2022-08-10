/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:05:14 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:27:39 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include <stdlib.h>
#include <math.h>

t_quat	quat_conjugate(t_quat q)
{
	return (quat_by_elements(q.w, -q.k.x, -q.k.y, -q.k.z));
}

t_quat	quat_inverse(t_quat q)
{
	t_quat	inv_q;

	inv_q = quat_conjugate(q);
	return (quat_normalize(inv_q));
}

/*
t_quat	*quat_mul(t_quat q1, t_quat q2)
{
	t_vec3	*temp1;
	t_vec3	*temp2;
	double	w;
	t_vec3	*k;

	w = (q1.w * q2.w) - vec3_dot(q1.k, q2.k);
	temp2 = cross(q1.k, q2.k);
	temp1 = v3_add(v3_scale(q1.k, q2.w), v3_scale(q2.k, q1.w));
	k = v3_add(temp1, temp2);
	free(temp1);
	free(temp2);
	return (quat_by_vector(w, k));
}
*/
t_quat	quat_mul(t_quat q1, t_quat q2)
{
	double	q[4];

	q[0] = (q1.w * q2.w) - v3_dot(q1.k, q2.k);
	q[1] = (q1.w * q2.k.x) + (q1.k.x * q2.w) + \
			(q1.k.y * q2.k.z) - (q1.k.z * q2.k.y);
	q[2] = (q1.w * q2.k.y) - (q1.k.x * q2.k.z) + \
			(q1.k.y * q2.w) + (q1.k.z * q2.k.x);
	q[3] = (q1.w * q2.k.z) + (q1.k.x * q2.k.y) - \
			(q1.k.y * q2.k.x) + (q1.k.z * q2.w);
	return (quat_by_elements(q[0], q[1], q[2], q[3]));
}
