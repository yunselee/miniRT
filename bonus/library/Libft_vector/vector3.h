/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:02:15 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/10 22:36:47 by dkim2            ###   ########.fr       */
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

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec3;

t_vec3	make_v3(double const x, double const y, double const z);

double	v3_l2norm(t_vec3 a);
t_vec3	v3_normalize(t_vec3 a);

t_vec3	v3_add(t_vec3 a, t_vec3 b);
t_vec3	v3_sub(t_vec3 a, t_vec3 b);
t_vec3	v3_mul(t_vec3 a, double const scaler);
double	v3_dot(t_vec3 a, t_vec3 b);
t_vec3	v3_crs(t_vec3 a, t_vec3 b);
int		v3_isnull(t_vec3 a);

#endif