/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:17:35 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 08:48:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX44_H
# define MATRIX44_H
# include "vector3.h"
# include "transform.h"

typedef struct s_mat44 
{
	t_vec4	col1;
	t_vec4	col2;
	t_vec4	col3;
	t_vec4	col4;
}	t_mat44  ;
//__attribute__((aligned(32 * 4))) 
t_mat44	create_mat44(t_vec4 v1, t_vec4 v2, t_vec4 v3, t_vec4 v4);

t_mat44	trans_mat44(t_mat44 a);

t_mat44	mul_mat44(t_mat44 a, t_mat44 b);

float	quadratic_form(t_vec4 v1, t_mat44 m, t_vec4 v2);

t_mat44	rotation_mat44(t_vec3 axis, double deg);

#endif