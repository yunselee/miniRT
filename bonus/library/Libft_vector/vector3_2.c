/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:06:19 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 18:11:45 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <stdlib.h>
#include <math.h>
#include <smmintrin.h>

//const t_vec3	c = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
//return (c);
t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	// const __m128			cc = *((__m128*)&a);
	// const __m128			dd = *((__m128*)&b);
	// const __m128			kk = _mm_sub_ps(cc, dd);
	// const t_vec3			*p = (t_vec3*)&kk;

	// return (*p);
	const t_vec3	c = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
	return (c);

}

t_vec3	v3_mul(t_vec3 a, double s)
{
	const t_vec3	n = {a.x * s, a.y * s, a.z * s, 0};

	return (n);
}

//	return (a.x * b.x + a.y * b.y + a.z * b.z);
//error
	// const __m128			cc = *((__m128*)&a);
	// const __m128			dd = *((__m128*)&b);
	// const __m128			kk = _mm_mul_ps(cc, dd);
	// const __m128			kkk = _mm_hadd_ps(kk, kk);

	// return (_mm_cvtss_f32(_mm_hadd_ps(kkk, kkk)));
double	v3_dot(t_vec3	a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	v3_crs(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	c.w = 0;
	return (c);
}

int	v3_isnull(t_vec3 a)
{
	if (fabs(a.x) < 0.001 && fabs(a.y) < 0.001 && fabs(a.z) < 0.001)
		return (TRUE);
	return (FALSE);
}
