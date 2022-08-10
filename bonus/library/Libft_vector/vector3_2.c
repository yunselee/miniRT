/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:06:19 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:27:49 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	return (make_v3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	v3_mul(t_vec3 a, double const s)
{
	t_vec3	n;

	n.x = a.x * s;
	n.y = a.y * s;
	n.z = a.z * s;
	return (n);
}

double	v3_dot(t_vec3	a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	v3_crs(t_vec3 a, t_vec3 b)
{
	double	x;
	double	y;
	double	z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return (make_v3(x, y, z));
}

int	v3_isnull(t_vec3 a)
{
	if (a.x == 0 && a.y == 0 && a.z == 0)
		return (TRUE);
	return (FALSE);
}
