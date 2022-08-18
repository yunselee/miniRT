/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_quadrics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:30:42 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/18 14:26:54 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "debug_msgs.h"
#include "scene_editer.h"

void	debug_find_intersection(const t_quadrics *Q, \
									const t_ray *ray)
{
	const char	*type[2] = {"Q_PLANE", "Q_QUADRICS"};

	if (get_scene_editer()->debug != D_DETAIL)
		return ;
	else if (Q && ray)
	{
		printf("\t qudrics type : %s\n", type[Q->type]);
		printf("\tray dir : <%f %f %f>\n", ray->dir.x, ray->dir.y, ray->dir.z);
		printf("\tray org : <%f %f %f>\n", ray->org.x, ray->org.y, ray->org.z);
	}
}

void	debug_z_range(const float zrange[2], \
						const float *sol, \
						const float *z)
{
	if (get_scene_editer()->debug != D_DETAIL)
		return ;
	if (zrange && sol && z)
	{
		printf("\tsolution is %f\n", *sol);
		printf("\tz_range: %f ~ %f, z_value: %f\n", zrange[0], zrange[1], *z);
		if (*z >= zrange[0] - EPSILON && *z <= zrange[1] + EPSILON)
			printf("\tVALID\n");
		else
			printf("\tINVALID\n");
	}
}

void	debug_solve_equation(const float coefs[3], \
							const float *D, \
							const float *sol1, \
							const float *sol2)
{
	if (get_scene_editer()->debug != D_DETAIL)
		return ;
	if (coefs && !D && !sol1 && !sol2)
		printf("\tEquation : (%f)t^2 + (%f)t + (%f) = 0\n", \
				coefs[0], coefs[1], coefs[2]);
	else if (!coefs && D && sol1 && sol2)
	{
		printf("\tDiscriminant : %f\n", *D);
		printf("\tSolutions : %f, %f\n\n", *sol1, *sol2);
	}
	else if (!coefs && !D && sol1 && !sol2)
		printf("\tSoultion : %f\n\n", *sol1);
}
