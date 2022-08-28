/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:02:15 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/28 11:58:29 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

#include <smmintrin.h>

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec;
//
typedef t_vec	t_vec3  __attribute__((aligned(sizeof(__m128))));

t_vec3	make_v3(double const x, double const y, double const z);
float	v3_l2norm(t_vec3 a);
t_vec3	v3_normalize(t_vec3 a);
t_vec3	v3_add(t_vec3 a, t_vec3 b);
t_vec3	v3_sub(t_vec3 a, t_vec3 b);
t_vec3	v3_mul(t_vec3 a, float const scaler);
float	v3_dot(t_vec3 a, t_vec3 b);
t_vec3	v3_crs(t_vec3 a, t_vec3 b);
int		v3_isnull(t_vec3 a);

typedef t_vec	t_vec4  __attribute__((aligned(sizeof(__m128))));
t_vec4	make_v4(float x, float y, float z, float w);
float	v4_l2norm(const t_vec4 *v);
t_vec4	v4_normalize(const t_vec4 *a);
t_vec4	v4_add(t_vec4 a, t_vec4 b);
t_vec4	v4_sub(t_vec4 a, t_vec4 b);
t_vec4	v4_mul(t_vec4 a, float const scaler);
float	v4_dot(t_vec4 a, t_vec4 b);
int		v4_isnull(t_vec4 a);

#endif