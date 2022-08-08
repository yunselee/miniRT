/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 04:50:53 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/08 18:53:24 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H
# include "matrix33.h"
# include "quaternion.h"

t_vec3	transform_by_mat33(t_mat33 T, t_vec3 x);
t_mat33	rotation_matrix(t_vec3	axis, double deg);
t_vec3	rotate_vec3_rad(t_vec3 axis, double rad, t_vec3 x);
t_vec3	rotate_vec3_deg(t_vec3 axis, double deg, t_vec3 x);

#endif