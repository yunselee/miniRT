/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:08:31 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/24 15:19:51 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quadrics.h"
#include <stdlib.h>
#include "libft.h"
#include "in_parsing.h"

t_quadrics	*free_return(t_quadrics	*quadric)
{
	free(quadric);
	return (FALSE);
}

void	rotate_quadrics(t_quadrics *Q, t_vec3 axis, float deg)
{
	t_mat44	rotation;

	Q->dir = rotate_vec3_deg(axis, deg, Q->dir);
	Q->tan = rotate_vec3_deg(axis, deg, Q->tan);
	rotation.col1 = rotate_vec3_deg(axis, deg, make_v3(1, 0, 0));
	rotation.col2 = rotate_vec3_deg(axis, deg, make_v3(0, 1, 0));
	rotation.col3 = rotate_vec3_deg(axis, deg, make_v3(0, 0, 1));
	rotation.col4 = make_v4(0, 0, 0, 1);
	Q->coefs = mul_mat44(trans_mat44(rotation), mul_mat44(Q->coefs, rotation));
}

t_quadrics	*case_quad_sphere(char **single_scene)
{
	t_quadrics	*newquad;

	if (ft_strsetlen(single_scene) != 4)
		return (NULL);
	newquad = ft_calloc(1, sizeof(t_quadrics));
	if ((str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
		|| (ft_strtof(single_scene[2], &newquad->coefs.col4.w) == FALSE) \
		|| (str_to_color(single_scene[3], &newquad->color) == FALSE))
	{
		free(newquad);
		return (NULL);
	}
	newquad->type = Q_QUADRICS;
	newquad->dir = make_v3(0, 0, 1);
	newquad->coefs.col4.w /= 2;
	newquad->range_z[0] = -newquad->coefs.col4.w;
	newquad->range_z[1] = newquad->coefs.col4.w;
	newquad->coefs.col4.w *= -newquad->coefs.col4.w;
	newquad->coefs.col1.x = 1;
	newquad->coefs.col2.y = 1;
	newquad->coefs.col3.z = 1;
	newquad->spec_rs = 0.2;
	newquad->spec_ns = 54;
	return (newquad);
}

t_quadrics	*case_quad_cylinder(char **cylinder_info)
{
	t_quadrics	*newquad;
	float		coef[5];

	newquad = ft_calloc(1, sizeof(t_quadrics));
	newquad->type = Q_QUADRICS;
	if (
		(ft_strsetlen(cylinder_info) < 6)
		|| (str_to_vec3(cylinder_info[1], &newquad->org) == FALSE)
		|| (str_to_vec3(cylinder_info[2], &newquad->dir) == FALSE)
		|| (ft_strtof(cylinder_info[3], coef + 4) == FALSE)
		|| (ft_strtof(cylinder_info[4], newquad->range_z + 1) == FALSE)
		|| (str_to_color(cylinder_info[5], &newquad->color) == FALSE) \
	)
		return (free_return(newquad));
	coef[0] = 1;
	coef[1] = 1;
	coef[2] = 0;
	coef[3] = 0;
	coef[4] = -(coef[4] * coef[4]) / 4;
	newquad->spec_rs = 0.2;
	newquad->spec_ns = 54;
	newquad->range_z[0] = 0;
	fill_quad_matrix(&newquad->coefs, coef);
	return (newquad);
}
