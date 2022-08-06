/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 07:30:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/26 15:30:23 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H
# include "vector3.h"

# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

typedef struct s_quat
{
	double	w;
	t_vec3	k;
}	t_quat;

t_quat	quat_by_elements(double const x, double const y, \
						double const z, double const w);

t_quat	quat_by_vector(double const w, t_vec3 k);

t_quat	quat_normalize(t_quat quat);

t_quat	quat_conjugate(t_quat quat);

t_quat	quat_inverse(t_quat quat);

double	quat_l2norm(t_quat quat);

t_quat	quat_mul(t_quat quat1, t_quat qaut2);

#endif