/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:55:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 22:28:56 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "quadrics.h"
#include "in_parsing.h"


// static void print_mat44(const t_mat44 *M)
// {
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.x, M->col2.x, M->col3.x, M->col4.x);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.y, M->col2.y, M->col3.y, M->col4.y);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.z, M->col2.z, M->col3.z, M->col4.z);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.w, M->col2.w, M->col3.w, M->col4.w);
// }


static void	ft_addlst_back(t_quadrics **objlst, t_quadrics *node)
{
	t_quadrics	*last;

	node->next = NULL;
	if (*objlst == NULL)
	{
		*objlst = node;
		return ;
	}
	last = *objlst;
	while (last->next)
		last = last->next;
	last->next = node;
}

static t_vec4	get_quad_tangential(const t_vec4 *unit_normal)
{
	if (unit_normal->y == 1)
		return ((t_vec4){1.0f, 0.0f, 0.0f, 0.0f});
	else if (unit_normal->y == -1)
		return ((t_vec4){-1.0f, 0.0f, 0.0f, 0.0f});
	else
		return (v3_normalize(v3_crs(make_v3(0, 1, 0), *unit_normal)));
}


static void	rotate_to_quad_dir(t_quadrics *Q)
{
	t_mat44	mat;

	mat.col1 = Q->tan;
	mat.col3 = Q->dir;
	mat.col2 = v3_normalize(v3_crs(Q->dir, Q->tan));
	mat.col4 = make_v4(0, 0, 0, 1);
	// print_mat44(&mat);
	Q->coefs = mul_mat44(mat, mul_mat44(Q->coefs, trans_mat44(mat)));
}

/*
	pl   : 평면(plane)
	
	sp   : 구(sphere)
		(x^2/r^2) + (y^2/r^2) + (z^2/r^2) = 1
	el   : 타원면(ellipsoid)
		(x^2/a^2) + (y^2/b^2) + (z^2/c^2) = 1
	
	cy   : 원기둥(cylinder)
		(x^2/r^2) + (y^2/r^2) = 1
	elcy : 타원기둥(elliptic Cylinder)
		(x^2/a^2) + (y^2/b^2) = 1
	hycy : 쌍곡기둥(hyperbolic Cylinder)
		(x^2/a^2) - (y^2/b^2) = 1
	pbcy : 포물기둥(Parabolic Cylinder)
		(x^2) + (2ay) = 0
	
	co   : 원뿔(cone)
		(x^2/a^2) + (y^2/a^2) - (z^2/b^2) = 1
	elco : 타원뿔(elliptic Cone)
		(x^2/a^2) + (y^2/b^2) - (z^2/c^2) = 1
	
	elpb : 타원포물면(elliptic paraboloid)
		(x^2/a^2) + (y^2/b^2) - z = 0
	hypb : 쌍곡포물면(Hyperbolic paraboloid)
		(x^2/a^2) - (y^2/b^2) - z = 0

	hb1  : 일엽쌍곡면(Hyperboloid one sheet)
		(x^2/a^2) + (y^2/b^2) - (z^2/c^2) = 1
	hb2  : 이엽쌍곡면(Hyperboloid two sheets)
		(x^2/a^2) + (y^2/b^2) -  (z^2/c^2) = -1
*/
int	init_quadrics(t_scene *outscene, char **single_scene)
{
	t_quadrics	*quadric;
	
	quadric = NULL;
	if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		quadric = case_quad_plane(single_scene);
	else if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		quadric = case_quad_sphere(single_scene);
	// else if (ft_strncmp(single_scene[0], "cy", 3) == 0)
	// 	quadric = case_cylinder(single_scene);
	else if (ft_strncmp(single_scene[0], "qd", 3) == 0)
		quadric = case_quadrics(single_scene);
	else
		return (FALSE);
	//...
	if ((quadric == NULL) \
		|| roundf(v3_l2norm(quadric->dir) * 10000) / 10000 != 1.0
		|| quadric->spec_rs < 0 || quadric->spec_rs >= 1 || quadric->spec_ns < 1)
	{
		free(quadric);
		return (FALSE);
	}
	quadric->tan = get_quad_tangential(&quadric->dir);
	rotate_to_quad_dir(quadric);
	ft_addlst_back(&(outscene->quads), quadric);
	return (TRUE);
}

void	free_quadlist(t_quadrics *quad_list)
{
	t_quadrics	*curr;
	t_quadrics	*next;

	curr = quad_list;
	while (curr)
	{
		next = curr -> next;
		free(curr);
		curr = next;
	}
}

// z = 0
t_quadrics	*case_quad_plane(char **single_scene)
{
	t_quadrics	*newquad;

	if (ft_strsetlen(single_scene) != 6)
		return (NULL);
	newquad = ft_calloc(1, sizeof(t_quadrics));
	if ((str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
		|| (str_to_vec3(single_scene[2], &newquad->dir) == FALSE) \
		|| (str_to_color(single_scene[3], &newquad->color) == FALSE) \
		|| (ft_strtof(single_scene[4], &newquad->spec_rs) == FALSE) \
		|| (ft_strtoi(single_scene[5], &newquad->spec_ns) == FALSE))
	{
		free(newquad);
		return (NULL);
	}
	newquad->type = Q_PLANE;
	newquad->coefs.col3.w = 1;
	newquad->coefs.col4.z = 1;
	return (newquad);
}

// x^2 + y^2 + z^2 - r^2 = 0
t_quadrics	*case_quad_sphere(char **single_scene)
{
	t_quadrics	*newquad;

	if (ft_strsetlen(single_scene) != 6)
		return (NULL);
	newquad = ft_calloc(1, sizeof(t_quadrics));
	if ((str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
		|| (ft_strtof(single_scene[2], &newquad->coefs.col4.w) == FALSE) \
		|| (str_to_color(single_scene[3], &newquad->color) == FALSE) \
		|| (ft_strtof(single_scene[4], &newquad->spec_rs) == FALSE) \
		|| (ft_strtoi(single_scene[5], &newquad->spec_ns) == FALSE))
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
	return (newquad);
}


// t_quadrics	*case_quad_cylinder(char **single_scene)
// {
// 	t_quadrics	*newquad;

// 	if (ft_strsetlen(single_scene) != 6)
// 		return (NULL);
// 	newquad = ft_calloc(1, sizeof(t_quadrics));
// 	if ((str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
// 		|| (ft_strtof(single_scene[2], &newquad->coefs.col4.w) == FALSE) \
// 		|| (str_to_color(single_scene[3], &newquad->color) == FALSE) \
// 		|| (ft_strtof(single_scene[4], &newquad->spec_rs) == FALSE) \
// 		|| (ft_strtoi(single_scene[5], &newquad->spec_ns) == FALSE))
// 	{
// 		free(newquad);
// 		return (NULL);
// 	}
// 	newquad->dir = make_v3(0, 0, 1);
// 	newquad->coefs.col4.w /= 2;
// 	newquad->range_z[0] = -newquad->coefs.col4.w;
// 	newquad->range_z[1] = newquad->coefs.col4.w;
// 	newquad->coefs.col4.w *= -newquad->coefs.col4.w;
// 	newquad->coefs.col1.x = 1;
// 	newquad->coefs.col2.y = 1;
// 	newquad->coefs.col3.z = 1;
// 	return (newquad);
// }

t_quadrics	*case_quadrics(char **single_scene)
{
	t_quadrics	*newquad;
	float		coef[5];
	
	if (ft_strsetlen(single_scene) != 13)
		return (NULL);
	newquad = ft_calloc(1, sizeof(t_quadrics));
	if ((str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
	|| (str_to_vec3(single_scene[2], &newquad->dir) == FALSE) \
	|| (ft_strtof(single_scene[3], coef + 0) == FALSE) \
	|| (ft_strtof(single_scene[4], coef + 1) == FALSE) \
	|| (ft_strtof(single_scene[5], coef + 2) == FALSE) \
	|| (ft_strtof(single_scene[6], coef + 3) == FALSE) \
	|| (ft_strtof(single_scene[7], coef + 4) == FALSE) \
	|| (ft_strtof(single_scene[8], newquad->range_z) == FALSE) \
	|| (ft_strtof(single_scene[9], newquad->range_z + 1) == FALSE) \
	|| (str_to_color(single_scene[10], &newquad->color) == FALSE) \
	|| (ft_strtof(single_scene[11], &newquad->spec_rs) == FALSE) \
	|| (ft_strtoi(single_scene[12], &newquad->spec_ns) == FALSE))
	{
		free(newquad);
		return (NULL);
	}
	newquad->coefs.col1 = make_v4(coef[0], 0, 0, 0);
	newquad->coefs.col2 = make_v4(0, coef[1], 0, 0);
	newquad->coefs.col3 = make_v4(0, 0, coef[2], coef[3]);
	newquad->coefs.col4 = make_v4(0, 0, coef[3], coef[4]);
	newquad->type = Q_QUADRICS;
	return (newquad);
}