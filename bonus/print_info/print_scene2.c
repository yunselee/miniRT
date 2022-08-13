/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:20:28 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 19:15:56 by dkim2            ###   ########.fr       */
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
	int	red;
	int	green;
	int	blue;

	red = Q->color.red;
	green = Q->color.green;
	blue = Q->color.blue;
	if (Q->type == Q_PLANE)
		printf("type : PLANE\n");
	else
		printf("type : QUADRICS\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", Q->org.x \
											, Q->org.y \
											, Q->org.z);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", Q->dir.x \
												, Q->dir.y \
												, Q->dir.z);
	printf("\ttangential : [%3.4f, %3.4f, %3.4f]\n", Q->tan.x \
												, Q->tan.y \
												, Q->tan.z);
	print_mat44(&Q->coefs);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n", red, green, blue);
	printf("\tspecular factors : Rs : %.2f Ns : %d\n\n", Q->spec_rs, Q->spec_ns);
	if (Q->bumpmap.img)
		printf("\t  bump map -> width : %d, height : %d\n", Q->bumpmap.img_width, Q->bumpmap.img_height);
	if (Q->texture.img)
		printf("\t  texture  -> width : %d, height : %d\n", Q->texture.img_width, Q->texture.img_height);
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
