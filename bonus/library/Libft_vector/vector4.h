/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:17:04 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 08:51:43 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR4_H
# define VECTOR4_H

#include "vector3.h"

float	v4_l2norm(const t_vec4 *a)
t_vec4	v4_normalize(const t_vec4 *a)

t_vec4	v4_add(t_vec4 a, t_vec4 b);
t_vec4	v4_sub(t_vec4 a, t_vec4 b);
t_vec4	v4_mul(t_vec4 a, double const scaler);
float	v4_dot(t_vec4 a, t_vec4 b);
t_vec4	v4_crs(t_vec4 a, t_vec4 b);
int		v4_isnull(t_vec4 a);

#endif
