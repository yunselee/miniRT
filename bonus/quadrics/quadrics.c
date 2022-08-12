/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:55:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 11:31:09 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "quadrics.h"
#include "in_parsing.h"

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

void	rotate_to_quad_dir(t_quadrics *Q)
{
	t_mat44	mat;

	mat.col1 = Q->tan;
	mat.col3 = Q->dir;
	mat.col2 = v3_normalize(v3_crs(Q->dir, Q->tan));
	mat.col4 = make_v4(0, 0, 0, 1);
	Q->coefs = mul_mat44(mat, mul_mat44(Q->coefs, trans_mat44(mat)));
}

int	init_quadrics(t_scene *outscene, char **single_scene)
{
	t_quadrics	*quadric;

	quadric = NULL;
	if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		quadric = case_quad_plane(single_scene);
	else if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		quadric = case_quad_sphere(single_scene);
	else if (ft_strncmp(single_scene[0], "qd", 3) == 0)
		quadric = case_quadrics(single_scene);
	else
		return (FALSE);
	if ((quadric == NULL) \
		|| roundf(v3_l2norm(quadric->dir) * 10000) / 10000 != 1.0
		|| quadric->spec_rs < 0 || quadric->spec_rs >= 1 \
		|| quadric->spec_ns < 1)
	{
		free(quadric);
		return (FALSE);
	}
	quadric->disruption = FALSE;
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
