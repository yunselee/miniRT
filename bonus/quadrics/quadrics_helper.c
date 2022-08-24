/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:46:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/24 15:44:10 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "quadrics.h"
#include "in_parsing.h"
#include <math.h>

static int	take_texture_files(t_quadrics *Q, char **quad_info)
{
	int		i;

	Q->textures[T_NORMAL].img.img = NULL;
	Q->textures[T_TEXTURE].img.img = NULL;
	i = -1;
	while (quad_info[++i] && i < 2)
	{
		if (ft_strncmp(quad_info[i], "NULL", 5) == 0)
			continue ;
		Q->textures[i].img.img = mlx_xpm_file_to_image((get_mlx())->mlx, \
			quad_info[i], &(Q->textures[i].img_width), \
			&(Q->textures[i].img_height));
		if (Q->textures[i].img.img == NULL)
			return (FALSE);
		Q->textures[i].img.addr = mlx_get_data_addr(Q->textures[i].img.img, \
			&Q->textures[i].img.bpp, &Q->textures[i].img.line, \
			&Q->textures[i].img.endian);
		if (Q->textures[i].img.addr == NULL)
			return (FALSE);
	}
	return (TRUE);
}

void	fill_quad_matrix(t_mat44 *mat, float coef[5])
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

t_quadrics	*case_quad_plane(char **quad_info)
{
	t_quadrics	*newquad;

	newquad = ft_calloc(1, sizeof(t_quadrics));
	newquad->spec_rs = 0.2;
	newquad->spec_ns = 54;
	if (((ft_strsetlen(quad_info) < 4) || (ft_strsetlen(quad_info) > 8)) \
		|| (str_to_vec3(quad_info[1], &newquad->org) == FALSE) \
		|| (str_to_vec3(quad_info[2], &newquad->dir) == FALSE) \
		|| (str_to_color(quad_info[3], &newquad->color) == FALSE) \
		)
		return (free_return(newquad));
	if ((ft_strsetlen(quad_info) > 4) && (ft_strsetlen(quad_info) <= 8))
	{
		if (ft_strtof(quad_info[4], &newquad->spec_rs) == FALSE \
		|| ft_strtoi(quad_info[5], &newquad->spec_ns) == FALSE \
		|| (take_texture_files(newquad, quad_info + 6) == FALSE))
			return (free_return(newquad));
	}
	newquad->type = Q_PLANE;
	newquad->coefs.col3.w = 1;
	newquad->coefs.col4.z = 1;
	return (newquad);
}

t_quadrics	*case_quad_cone(char **cylinder_info)
{
	t_quadrics	*newquad;
	float		coef[5];
	float		degree;

	newquad = ft_calloc(1, sizeof(t_quadrics));
	newquad->type = Q_QUADRICS;
	if ((ft_strsetlen(cylinder_info) < 5) \
		|| (str_to_vec3(cylinder_info[1], &newquad->org) == FALSE) \
		|| (str_to_vec3(cylinder_info[2], &newquad->dir) == FALSE) \
		|| (ft_strtof(cylinder_info[3], &degree) == FALSE) \
		|| (str_to_color(cylinder_info[4], &newquad->color) == FALSE))
		return (free_return(newquad));
	newquad->spec_rs = 0.2;
	newquad->spec_ns = 54;
	newquad->range_z[0] = 0;
	newquad->range_z[1] = 40;
	coef[0] = 1600;
	coef[1] = 1600;
	coef[2] = -((tan(degree * M_PI / 180) * newquad->range_z[1]) * \
				(tan(degree * M_PI / 180) * newquad->range_z[1]));
	coef[3] = 0;
	coef[4] = 0;
	fill_quad_matrix(&newquad->coefs, coef);
	return (newquad);
}

t_quadrics	*case_quadrics(char **quad_info)
{
	t_quadrics	*newquad;
	float		coef[5];

	newquad = ft_calloc(1, sizeof(t_quadrics));
	newquad->type = Q_QUADRICS;
	if (((ft_strsetlen(quad_info) < 13) || (ft_strsetlen(quad_info) > 15)) \
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
		return (free_return(newquad));
	fill_quad_matrix(&newquad->coefs, coef);
	return (newquad);
}
