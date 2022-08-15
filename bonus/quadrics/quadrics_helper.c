/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:46:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/15 14:30:41 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "quadrics.h"
#include "in_parsing.h"

static int	take_texture_files(t_quadrics *Q, char** quad_info)
{
	t_xpm	*xpm;
	int		i;
	
	Q->bumpmap.img.img = NULL;
	Q->texture.img.img = NULL;
	xpm = &(Q->bumpmap);
	i = -1;
	while (quad_info[++i] && i < 2)
	{
		if (ft_strncmp(quad_info[0], "NULL", 5) == 0)
		{
			xpm = &(Q->texture);
			continue ;
		}
		xpm->img.img = mlx_xpm_file_to_image((get_mlx())->mlx, quad_info[i], \
										&(xpm->img_width), &(xpm->img_height));
		if (xpm->img.img == NULL)
			return (FALSE);
		xpm->img.addr = mlx_get_data_addr(xpm->img.img, &xpm->img.bpp, \
										&xpm->img.line, &xpm->img.endian);
		if (xpm->img.addr == NULL)
			return (FALSE);
		xpm = &(Q->texture);
	}
	return (TRUE);
}

t_quadrics	*case_quad_plane(char **quad_info)
{
	t_quadrics	*newquad;

	newquad = ft_calloc(1, sizeof(t_quadrics));
	if (((ft_strsetlen(quad_info) < 6) || (ft_strsetlen(quad_info) > 8) ) \
		|| (str_to_vec3(quad_info[1], &newquad->org) == FALSE) \
		|| (str_to_vec3(quad_info[2], &newquad->dir) == FALSE) \
		|| (str_to_color(quad_info[3], &newquad->color) == FALSE) \
		|| (ft_strtof(quad_info[4], &newquad->spec_rs) == FALSE) \
		|| (ft_strtoi(quad_info[5], &newquad->spec_ns) == FALSE) \
		|| (take_texture_files(newquad, quad_info + 6) == FALSE))
	{
		free_quadlist(newquad);
		return (NULL);
	}
	newquad->type = Q_PLANE;
	newquad->coefs.col3.w = 1;
	newquad->coefs.col4.z = 1;
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

t_quadrics	*case_quadrics(char **quad_info)
{
	t_quadrics	*newquad;
	float		coef[5];

	newquad = ft_calloc(1, sizeof(t_quadrics));
	newquad->type = Q_QUADRICS;
	if (((ft_strsetlen(quad_info) < 13) || (ft_strsetlen(quad_info) > 15) ) \
		|| (str_to_vec3(quad_info[1], &newquad->org) == FALSE) \
		|| (str_to_vec3(quad_info[2], &newquad->dir) == FALSE) \
		|| (ft_strtof(quad_info[3], coef + 0) == FALSE) \
		|| (ft_strtof(quad_info[4], coef + 1) == FALSE) \
		|| (ft_strtof(quad_info[5], coef + 2) == FALSE) \
		|| (ft_strtof(quad_info[6], coef + 3) == FALSE) \
		|| (ft_strtof(quad_info[7], coef + 4) == FALSE) \
		|| (ft_strtof(quad_info[8], newquad->range_z) == FALSE) \
		|| (ft_strtof(quad_info[9], newquad->range_z + 1) == FALSE) \
		|| (str_to_color(quad_info[10], &newquad->color) == FALSE) \
		|| (ft_strtof(quad_info[11], &newquad->spec_rs) == FALSE) \
		|| (ft_strtoi(quad_info[12], &newquad->spec_ns) == FALSE) \
		|| (take_texture_files(newquad, quad_info + 13) == FALSE))
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
