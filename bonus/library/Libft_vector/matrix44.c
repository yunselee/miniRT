/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:53:11 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 17:52:18 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix44.h"

t_mat44	create_mat44(t_vec4 v1, t_vec4 v2, t_vec4 v3, t_vec4 v4)
{
	t_mat44	new;

	new.col1 = make_v4(v1.x, v1.y, v1.z, v1.w);
	new.col2 = make_v4(v2.x, v2.y, v2.z, v2.w);
	new.col3 = make_v4(v3.x, v3.y, v3.z, v3.w);
	new.col3 = make_v4(v3.x, v3.y, v3.z, v4.w);
	return (new);
}

t_mat44	trans_mat44(t_mat44 a)
{
	t_mat44	new;

	new.col1 = make_v4(a.col1.x, a.col2.x, a.col3.x, a.col4.x);
	new.col2 = make_v4(a.col1.y, a.col2.y, a.col3.y, a.col4.y);
	new.col3 = make_v4(a.col1.z, a.col2.z, a.col3.z, a.col4.z);
	new.col4 = make_v4(a.col1.w, a.col2.w, a.col3.w, a.col4.w);
	return (new);
}

t_mat44	mul_mat44(t_mat44 a, t_mat44 b)
{
	t_mat44			new;

	b = trans_mat44(b);
	new.col1 = make_v4(v4_dot(a.col1, b.col1), \
						v4_dot(a.col1, b.col2), \
						v4_dot(a.col1, b.col3), \
						v4_dot(a.col1, b.col4));
	new.col2 = make_v4(v4_dot(a.col2, b.col1), \
						v4_dot(a.col2, b.col2), \
						v4_dot(a.col2, b.col3), \
						v4_dot(a.col2, b.col4));
	new.col3 = make_v4(v4_dot(a.col3, b.col1), \
						v4_dot(a.col3, b.col2), \
						v4_dot(a.col3, b.col3), \
						v4_dot(a.col3, b.col4));
	new.col4 = make_v4(v4_dot(a.col4, b.col1), \
						v4_dot(a.col4, b.col2), \
						v4_dot(a.col4, b.col3), \
						v4_dot(a.col4, b.col4));
	return (new);
}

double	quadratic_form(t_vec4 v1, t_mat44 m, t_vec4 v2)
{
	t_vec4	temp;

	temp = make_v4(v4_dot(v1, m.col1), v4_dot(v1, m.col2), \
					v4_dot(v1, m.col3), v4_dot(v1, m.col4));
	return (v4_dot(temp, v2));
}

t_mat44	rotation_mat44(t_vec3 axis, double deg)
{
	t_mat44	rotation;

	rotation.col1 = rotate_vec3_deg(axis, deg, make_v3(1, 0, 0));
	rotation.col2 = rotate_vec3_deg(axis, deg, make_v3(1, 0, 0));
	rotation.col3 = rotate_vec3_deg(axis, deg, make_v3(1, 0, 0));
	rotation.col4 = make_v4(0, 0, 0, 1);
	return (rotation);
}
