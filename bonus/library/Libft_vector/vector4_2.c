/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:23:14 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 17:52:49 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <smmintrin.h>

t_vec4	v4_sub(t_vec4 a, t_vec4 b)
{
	return (v3_sub(a, b));
}

t_vec4	v4_mul(t_vec4 a, double const s)
{
	const t_vec4	n = {a.x * s, a.y * s, a.z * s, a.w * s};

	return (n);
}

double	v4_dot(t_vec4	a, t_vec4 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

int	v4_isnull(t_vec4 a)
{
	if (a.x == 0 && a.y == 0 && a.z == 0 && a.w == 0)
		return (1);
	return (0);
}
