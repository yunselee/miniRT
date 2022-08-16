/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:20:23 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 19:25:15 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>
#include <smmintrin.h>

t_vec4	make_v4(double x, double y, double z, double w)
{
	const t_vec4	new_vec4 = {x, y, z, w};

	return (new_vec4);
}

double	v4_l2norm(t_vec4 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec4	v4_normalize(t_vec4 a)
{
	const double	len = v4_l2norm(a);
	const t_vec4	n = {a.x / len, a.y / len, a.z / len, a.w / len};

	return (n);
}

t_vec4	v4_add(t_vec4 a, t_vec4 b)
{
	return (v3_add(a, b));
}
