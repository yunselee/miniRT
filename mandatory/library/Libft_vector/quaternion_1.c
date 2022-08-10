/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:32:33 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:27:06 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include <stdlib.h>
#include <math.h>

t_quat	quat_by_elements(double const w, double const x, \
						double const y, double const z)
{
	t_quat	q;
	t_vec3	k;

	k = make_v3(x, y, z);
	q = quat_by_vector(w, k);
	return (q);
}

t_quat	quat_by_vector(double const w, t_vec3 k)
{
	t_quat	q;

	q.w = w;
	q.k = make_v3(k.x, k.y, k.z);
	return (q);
}

double	quat_l2norm(t_quat q)
{
	double	length;

	length = pow(q.w, 2) + pow(v3_l2norm(q.k), 2);
	length = sqrt(length);
	return (length);
}

t_quat	quat_normalize(t_quat q)
{
	t_quat	n;
	double	norm;

	norm = quat_l2norm(q);
	if (norm == 0)
		return (q);
	n.w = q.w / norm;
	n.k.x = q.k.x / norm;
	n.k.y = q.k.y / norm;
	n.k.z = q.k.z / norm;
	return (n);
}
