/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:05:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:27:24 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <stdlib.h>
#include <math.h>

t_vec3	make_v3(double const x, double const y, double const z)
{
	t_vec3	new_vec3;

	new_vec3.x = x;
	new_vec3.y = y;
	new_vec3.z = z;
	return (new_vec3);
}

double	v3_l2norm(t_vec3 a)
{
	double	length;

	length = pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2);
	length = sqrt(length);
	return (length);
}

t_vec3	v3_normalize(t_vec3 a)
{
	t_vec3	n;
	double	length;

	length = v3_l2norm(a);
	n.x = a.x / length;
	n.y = a.y / length;
	n.z = a.z / length;
	return (n);
}

t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	return (make_v3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_dup(t_vec3 a)
{
	return (make_v3(a.x, a.y, a.z));
}
