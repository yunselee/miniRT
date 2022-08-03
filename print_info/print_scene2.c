/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:20:28 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:29:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../LIBFT/libft.h"
#include "scene.h"
#include "print_info.h"

static void	info_plane(t_object_base *obj)
{
	int	red;
	int	green;
	int	blue;

	red = obj->color.red;
	green = obj->color.green;
	blue = obj->color.blue;
	printf("\ttype : PLANE\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->org.x \
											, obj->org.y \
											, obj->org.z);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", obj->org.x \
												, obj->org.y \
												, obj->org.z);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n\n", red, green, blue);
}

static void	info_sphere(t_object_base *obj)
{
	int	red;
	int	green;
	int	blue;

	red = obj->color.red;
	green = obj->color.green;
	blue = obj->color.blue;
	printf("\ttype : SPHERE\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->org.x \
											, obj->org.y \
											, obj->org.z);
	printf("\tradius : %3.4f\n", obj->radius);
	printf ("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n\n", red, green, blue);
}

static void	info_cylinder(t_object_base *obj)
{
	int	red;
	int	green;
	int	blue;

	red = obj->color.red;
	green = obj->color.green;
	blue = obj->color.blue;
	printf("\ttype : CYLINDER\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->org.x \
											, obj->org.y \
											, obj->org.z);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", obj->normal.x \
												, obj->normal.y \
												, obj->normal.z);
	printf("\tradius : %3.4f\n", obj->radius);
	printf("\theight : %3.4f\n", obj->height);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n\n", red, green, blue);
}

void	print_info_object(t_object_base *obj)
{
	if (obj == NULL)
		printf("ERR object error : Nullptr\n");
	if (obj->type == E_PLANE)
		info_plane(obj);
	else if (obj->type == E_SPHERE)
		info_sphere(obj);
	else if (obj->type == E_CYLINDER)
		info_cylinder(obj);
	if (obj->next)
		print_info_object(obj->next);
}
