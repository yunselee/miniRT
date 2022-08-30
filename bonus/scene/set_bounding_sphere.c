/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bounding_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:41:49 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/30 16:05:56 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "quadrics.h"

static float	radius_square(const t_quadrics *Q, float z)
{
	float	a;
	float	denominator;

	a = Q->coefs.col3.z * z * z + 2 * Q->coefs.col3.w * z + Q->coefs.col4.w;
	if (Q->coefs.col1.x >= Q->coefs.col2.y)
		denominator = Q->coefs.col2.y;
	else
		denominator = Q->coefs.col1.x;
	return (z * z - a / denominator);
}	

float	get_bounding_radius_square(const t_quadrics *Q)
{
	float	rad_square;

	if (Q->type == Q_PLANE)
		return (INFINITY);
	rad_square = fmax(radius_square(Q, Q->range_z[0]), radius_square(Q, 0));
	rad_square = fmax(rad_square, radius_square(Q, Q->range_z[1]));
	rad_square = fmax(rad_square, 0);
	return (rad_square);
}
