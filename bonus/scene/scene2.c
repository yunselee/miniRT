/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 05:05:37 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 19:54:59 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "quadrics.h"
#include "../LIBFT/libft.h"
#include "../Libft_vector/transform.h"
#include <stdio.h>

// static void print_mat44(const t_mat44 *M)
// {
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.x, M->col2.x, M->col3.x, M->col4.x);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.y, M->col2.y, M->col3.y, M->col4.y);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.z, M->col2.z, M->col3.z, M->col4.z);
// 	printf("|% .3f % .3f % .3f % .3f|\n", M->col1.w, M->col2.w, M->col3.w, M->col4.w);
// }

static void	transform_lights(t_light *light, t_mat33 transform, t_vec3 campos)
{
	t_light	*curr;

	curr = light;
	while (curr)
	{
		curr->o = v3_sub(curr->o, campos);
		curr->o = transform_by_mat33(transform, (curr->o));
		curr = curr->next;
	}
}

static void	transform_quadrics(t_quadrics *obj, t_mat33 transform, t_vec3 campos)
{
	t_quadrics	*curr;
	t_mat44		trans;
	t_mat44		transt;

	trans.col1 = transform.r1;
	trans.col2 = transform.r2;
	trans.col3 = transform.r3;
	trans.col4 = make_v4(0, 0, 0, 1);
	transt = trans_mat44(trans);
	curr = obj;
	while (curr)
	{
		{
			// printf("&&&&&&&&&&&&&&&&&&&&&&&&&\n");
			// print_mat44(&transt);
			// printf("*\n");
			// print_mat44(&curr->coefs);
			// printf("*\n");
			// print_mat44(&trans);
			// t_mat44 res = mul_mat44(transt, mul_mat44(curr->coefs, trans));
			// printf("=\n");
			// print_mat44(&res);
		}
		curr->org = v3_sub(curr->org, campos);
		curr->org = transform_by_mat33(transform, (curr->org));
		curr->dir = transform_by_mat33(transform, (curr->dir));
		curr->tan = transform_by_mat33(transform, (curr->dir));
		curr->coefs = mul_mat44(transt, curr->coefs);
		curr->coefs = mul_mat44(curr->coefs, trans);
		curr = curr->next;
	}
}

int	transform_to_cam_cord(t_scene *scene, t_mat33 transform)
{
	transform_lights(scene->light, transform, scene->cam->pos);
	transform_quadrics(scene->quads, transform, scene->cam->pos);
	scene->cam->pos = v3_sub(scene->cam->pos, scene->cam->pos);
	scene->cam->pos = transform_by_mat33(transform, (scene->cam->pos));
	scene->cam->dir = transform_by_mat33(transform, (scene->cam->dir));
	scene->global = mul_mat33(scene->global, transform);
	return (TRUE);
}
