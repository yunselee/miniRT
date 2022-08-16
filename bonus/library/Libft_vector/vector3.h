/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:02:15 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 17:52:35 by dkim2            ###   ########.fr       */
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

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec;

typedef t_vec	t_vec3;

t_vec3	make_v3(double const x, double const y, double const z);
double	v3_l2norm(t_vec3 a);
t_vec3	v3_normalize(t_vec3 a);
t_vec3	v3_add(t_vec3 a, t_vec3 b);
t_vec3	v3_sub(t_vec3 a, t_vec3 b);
t_vec3	v3_mul(t_vec3 a, double const scaler);
double	v3_dot(t_vec3 a, t_vec3 b);
t_vec3	v3_crs(t_vec3 a, t_vec3 b);
int		v3_isnull(t_vec3 a);

typedef t_vec	t_vec4;
t_vec4	make_v4(double x, double y, double z, double w);
double	v4_l2norm(t_vec4 v);
t_vec4	v4_normalize(t_vec4 a);
t_vec4	v4_add(t_vec4 a, t_vec4 b);
t_vec4	v4_sub(t_vec4 a, t_vec4 b);
t_vec4	v4_mul(t_vec4 a, double const scaler);
double	v4_dot(t_vec4 a, t_vec4 b);
int		v4_isnull(t_vec4 a);

#endif