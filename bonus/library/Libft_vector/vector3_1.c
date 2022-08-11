/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:05:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 20:47:07 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <stdlib.h>
#include <math.h>
#include <smmintrin.h>

//안한게 더 빠름 const __m128			cc = *((__m128*)&a);
// const __m128			kk = _mm_mul_ps(cc, cc);
// const __m128			kkk = _mm_hadd_ps(kk, kk);
// return (_mm_cvtss_f32(_mm_sqrt_ps(_mm_hadd_ps(kkk, kkk))));
t_vec3	make_v3(double const x, double const y, double const z)
{
	const t_vec3	new_vec3 = {x, y, z, 0};

	return (new_vec3);
}

// const double	len = v3_l2norm(a);
// const t_vec3	n = {a.x / len, a.y / len, a.z / len, a.w / len};
// return (n);
float	v3_l2norm(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

// const __m128			cc = *((__m128*)&a);
// const __m128			s = _mm_mul_ps(cc, cc);
// const __m128			l = _mm_hadd_ps(s, s);
// const __m128			no = _mm_mul_ps(cc, _mm_rsqrt_ps((_mm_hadd_ps(l, l))));
// const t_vec3			*p = (t_vec3 *)&no;
// return (*p);
t_vec3	v3_normalize(t_vec3 a)
{

	const float		len = v3_l2norm(a);
	const t_vec3	n = {a.x / len, a.y / len, a.z / len, a.w};
	return (n);

}

// return (make_v3(a.x + b.x, a.y + b.y, a.z + b.z))
t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	const __m128			cc = *((__m128*)&a);
	const __m128			dd = *((__m128*)&b);
	const __m128			kk = _mm_add_ps(cc, dd);
	const t_vec3			*p = (t_vec3*)&kk;

	return (*p);
}

t_vec3	vec3_dup(t_vec3 a)
{
	return (make_v3(a.x, a.y, a.z));
}
