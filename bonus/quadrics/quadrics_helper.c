/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:46:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/14 00:37:51 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "quadrics.h"
#include "in_parsing.h"


#include <stdio.h>
// z = 0
t_quadrics	*case_quad_plane(char **single_scene)
{
	t_quadrics	*newquad;
	int res;

	res = TRUE;
	if (ft_strsetlen(single_scene) < 6 || ft_strsetlen(single_scene) > 8)
		return (NULL);
	newquad = ft_calloc(1, sizeof(t_quadrics));
	if ((str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
		|| (str_to_vec3(single_scene[2], &newquad->dir) == FALSE) \
		|| (str_to_color(single_scene[3], &newquad->color) == FALSE) \
		|| (ft_strtof(single_scene[4], &newquad->spec_rs) == FALSE) \
		|| (ft_strtoi(single_scene[5], &newquad->spec_ns) == FALSE))
		res = FALSE;
	newquad->bumpmap.img = NULL;
	newquad->texture.img = NULL;
	t_mlx *mlx = get_mlx();
	if ((res == TRUE) && (ft_strsetlen(single_scene) > 6) && (ft_strncmp(single_scene[6], "NULL", 5) != 0))
	{
		newquad->bumpmap.img = mlx_xpm_file_to_image(mlx->mlx, single_scene[6], &(newquad->bumpmap.img_width), &(newquad->bumpmap.img_height));
		if (newquad->bumpmap.img == NULL)
			res = FALSE;
		newquad->bumpmap.addr = (int *)mlx_get_data_addr(newquad->bumpmap.img, &newquad->bumpmap.bpp, &newquad->bumpmap.line, &newquad->bumpmap.endian);
		if (newquad->bumpmap.addr == NULL)
			res = FALSE;
	}
	if ((res == TRUE) && (ft_strsetlen(single_scene) > 7))
	{
		newquad->texture.img = mlx_xpm_file_to_image(mlx->mlx, single_scene[7], &(newquad->texture.img_width), &(newquad->texture.img_height));
		if (newquad->texture.img == NULL)
			res = FALSE;
		newquad->texture.addr = (int *)mlx_get_data_addr(newquad->texture.img, &(newquad->texture.bpp), &(newquad->texture.line), &(newquad->texture.endian));
		if (newquad->texture.addr == NULL)
			res = FALSE;
	}
	if (res == FALSE)
	{
		free_quadlist(newquad);
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

static void	fill_quad_matrix(t_mat44 *mat, float coef[5])
{
	if (coef[0] < 0)
	{
		coef[0] = -coef[0];
		coef[1] = -coef[1];
		coef[2] = -coef[2];
		coef[3] = -coef[3];
		coef[4] = -coef[4];
	}
	mat->col1 = make_v4(coef[0], 0, 0, 0);
	mat->col2 = make_v4(0, coef[1], 0, 0);
	mat->col3 = make_v4(0, 0, coef[2], coef[3]);
	mat->col4 = make_v4(0, 0, coef[3], coef[4]);
}

t_quadrics	*case_quadrics(char **single_scene)
{
	t_quadrics	*newquad;
	int			res;
	float		coef[5];

	res = TRUE;
	newquad = ft_calloc(1, sizeof(t_quadrics));
	newquad->type = Q_QUADRICS;
	printf("strsetlen : %d\n", ft_strsetlen(single_scene));
	if (((ft_strsetlen(single_scene) < 13) || (ft_strsetlen(single_scene) > 15) ) \
	|| (str_to_vec3(single_scene[1], &newquad->org) == FALSE) \
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
		res = FALSE;
	newquad->bumpmap.img = NULL;
	newquad->texture.img = NULL;
	t_mlx *mlx = get_mlx();
	if ((res == TRUE) && (ft_strsetlen(single_scene) > 13) && (ft_strncmp(single_scene[13], "NULL", 5) != 0))
	{
		printf("XPM filename : <%s>\n", single_scene[13]);
		newquad->bumpmap.img = mlx_xpm_file_to_image(mlx->mlx, single_scene[13], &(newquad->bumpmap.img_width), &(newquad->bumpmap.img_height));
		if (newquad->bumpmap.img == NULL)
			res = FALSE;
		newquad->bumpmap.addr = (int *)mlx_get_data_addr(newquad->bumpmap.img, &newquad->bumpmap.bpp, &newquad->bumpmap.line, &newquad->bumpmap.endian);
	}
	if ((res == TRUE) && (ft_strsetlen(single_scene) > 14))
	{
		printf("XPM filename : <%s>\n", single_scene[14]);
		newquad->texture.img = mlx_xpm_file_to_image(mlx->mlx, single_scene[14], &(newquad->texture.img_width), &(newquad->texture.img_height));
		if (newquad->texture.img == NULL)
			res = FALSE;
		newquad->texture.addr = (int *)mlx_get_data_addr(newquad->texture.img, &(newquad->texture.bpp), &(newquad->texture.line), &(newquad->texture.endian));
	}
	if (res == FALSE)
	{
		free_quadlist(newquad);
		return (NULL);
	}
	fill_quad_matrix(&newquad->coefs, coef);
	return (newquad);
}

void	rotate_quadrics(t_quadrics *Q, t_vec3 axis, float deg)
{
	t_mat44	rotation;

	rotation.col1 = rotate_vec3_deg(axis, deg, make_v3(1, 0, 0));
	rotation.col2 = rotate_vec3_deg(axis, deg, make_v3(0, 1, 0));
	rotation.col3 = rotate_vec3_deg(axis, deg, make_v3(0, 0, 1));
	rotation.col4 = make_v4(0, 0, 0, 1);
	Q->coefs = mul_mat44(trans_mat44(rotation), mul_mat44(Q->coefs, rotation));
}
