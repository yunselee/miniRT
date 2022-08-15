/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:20:28 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/15 16:43:10 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../LIBFT/libft.h"
#include "print_info.h"

static void	print_mat44(const t_mat44 *M)
{
	printf("\t|% .3f % .3f % .3f % .3f|\n", \
			M->col1.x, M->col2.x, M->col3.x, M->col4.x);
	printf("\t|% .3f % .3f % .3f % .3f|\n", \
			M->col1.y, M->col2.y, M->col3.y, M->col4.y);
	printf("\t|% .3f % .3f % .3f % .3f|\n", \
			M->col1.z, M->col2.z, M->col3.z, M->col4.z);
	printf("\t|% .3f % .3f % .3f % .3f|\n", \
			M->col1.w, M->col2.w, M->col3.w, M->col4.w);
}

void	print_single_quadrics(const t_quadrics *Q)
{
	const int	rgb[3] = {Q->color.red, Q->color.green, Q->color.blue};

	if (Q->type == Q_PLANE)
		printf("type : PLANE\n");
	else
		printf("type : QUADRICS\n");
	printf("\torg : [%.4f, %.4f, %.4f]\n", Q->org.x, Q->org.y, Q->org.z);
	printf("\tnormal : [%.4f, %.4f, %.4f]\n", Q->dir.x, Q->dir.y, Q->dir.z);
	printf("\ttangential : [%.4f, %.4f, %.4f]\n", Q->tan.x, Q->tan.y, Q->tan.z);
	print_mat44(&Q->coefs);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", rgb[0], rgb[1], rgb[2]);
	printf(" : r: %d g: %d b: %d\n", rgb[0], rgb[1], rgb[2]);
	printf("\tspecular factors : Rs : %.2f Ns : %d\n\n", Q->spec_rs, Q->spec_ns);
	if (Q->textures[T_NORMAL].img.img)
		printf("\t  normal map -> width : %d, height : %d\n", \
		Q->textures[T_NORMAL].img_width, Q->textures[T_NORMAL].img_height);
	if (Q->textures[T_HEIGHT].img.img)
		printf("\t  texture  -> width : %d, height : %d\n", \
		Q->textures[T_HEIGHT].img_width, Q->textures[T_HEIGHT].img_height);
	if (Q->textures[T_TEXTURE].img.img)
		printf("\t  texture  -> width : %d, height : %d\n", \
		Q->textures[T_TEXTURE].img_width, Q->textures[T_TEXTURE].img_height);
}

void	print_info_quads(const t_quadrics *Qlst)
{
	const t_quadrics	*obj;

	obj = Qlst;
	while (obj)
	{
		print_single_quadrics(obj);
		obj = obj->next;
	}
}
