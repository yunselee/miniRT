/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix33.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:42:11 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 17:40:33 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix33.h"

t_mat33	create_mat33(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_mat33	new;

	new.r1 = make_v3(v1.x, v1.y, v1.z);
	new.r2 = make_v3(v2.x, v2.y, v2.z);
	new.r3 = make_v3(v3.x, v3.y, v3.z);
	return (new);
}

t_mat33	mat33_trans(t_mat33 m)
{
	t_mat33	new;

	new.r1 = make_v3(m.r1.x, m.r2.x, m.r3.x);
	new.r2 = make_v3(m.r1.y, m.r2.y, m.r3.y);
	new.r3 = make_v3(m.r1.z, m.r2.z, m.r3.z);
	return (new);
}

t_mat33	add_mat33(t_mat33 m1, t_mat33 m2)
{
	t_mat33	new;

	new.r1 = make_v3(m1.r1.x + m2.r1.x, \
						m1.r1.y + m2.r1.y, \
						m1.r1.z + m2.r1.z);
	new.r2 = make_v3(m1.r2.x + m2.r2.x, \
						m1.r2.y + m2.r2.y, \
						m1.r2.z + m2.r2.z);
	new.r3 = make_v3(m1.r3.x + m2.r3.x, \
						m1.r3.y + m2.r3.y, \
						m1.r3.z + m2.r3.z);
	return (new);
}

t_mat33	subtract_mat33(t_mat33 m1, t_mat33 m2)
{
	t_mat33	new;

	new.r1 = make_v3(m1.r1.x - m2.r1.x, \
						m1.r1.y - m2.r1.y, \
						m1.r1.z - m2.r1.z);
	new.r2 = make_v3(m1.r2.x - m2.r2.x, \
						m1.r2.y - m2.r2.y, \
						m1.r2.z - m2.r2.z);
	new.r3 = make_v3(m1.r3.x - m2.r3.x, \
						m1.r3.y - m2.r3.y, \
						m1.r3.z - m2.r3.z);
	return (new);
}

t_mat33	mul_mat33(t_mat33 m1, t_mat33 m2)
{
	t_mat33	new;

	m1 = mat33_trans(m1);
	new.r1 = make_v3(v3_dot(m1.r1, m2.r1), \
						v3_dot(m1.r1, m2.r2), \
						v3_dot(m1.r1, m2.r3));
	new.r2 = make_v3(v3_dot(m1.r2, m2.r1), \
						v3_dot(m1.r2, m2.r2), \
						v3_dot(m1.r2, m2.r3));
	new.r3 = make_v3(v3_dot(m1.r3, m2.r1), \
						v3_dot(m1.r3, m2.r2), \
						v3_dot(m1.r3, m2.r3));
	return (new);
}
