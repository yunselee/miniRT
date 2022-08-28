/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:20:23 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/28 12:06:05 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>
#include <smmintrin.h>

t_vec4	make_v4(float x, float y, float z, float w)
{
	const t_vec4	new_vec4 = {x, y, z, w};

	return (new_vec4);
}

	// const __m128			cc = *((__m128*)&a);
	// const __m128			dd = *((__m128*)&b);
	// const __m128			kk = _mm_mul_ps(cc, dd);
	// const __m128			kkk = _mm_hadd_ps(kk, kk);

	// return (_mm_cvtss_f32(_mm_hadd_ps(kkk, kkk)));

float	v4_l2norm(const t_vec4 *a)
{
	const __m128			cc = *((__m128*)a);
	const __m128			kk = _mm_mul_ps(cc, cc);
	const __m128			kkk = _mm_hadd_ps(kk, kk);

	return (_mm_cvtss_f32(_mm_sqrt_ss(_mm_hadd_ps(kkk, kkk))));
//	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}
t_vec4	v4_normalize(const t_vec4 *a)
{
	const __m128			cc = *((__m128*)a);
	const __m128			kk = _mm_mul_ps(cc, cc);
	const __m128			kkk = _mm_hadd_ps(kk, kk);
	 const __m128			kkkk = _mm_rsqrt_ss(_mm_hadd_ps(kkk, kkk));
	 const  __m128 ret = _mm_mul_ps(cc, kkkk);
	const t_vec4					*p = (t_vec4 *)&ret;
	return (*p);

	// const float len = v4_l2norm(a);
	
	// return make_v4(a.x/len, a.y/len, a.z/len, a.w/len);
}

t_vec4	v4_add(t_vec4 a, t_vec4 b)
{
	return (v3_add(a, b));
}
