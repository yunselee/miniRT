/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:11:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 15:42:51 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "scene.h"
#include "../LIBFT/libft.h"
#include "print_info.h"

void	print_single_light(const t_light *light)
{
	printf("[LIGHT]\n");
	printf("\tpos : [%3.4f, %3.4f, %3.4f]\n", light->o.x \
											, light->o.y \
											, light->o.z);
	printf("\tbrightness : %3.4f\n", light->bright);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", light->color.red, \
												light->color.green, \
												light->color.blue);
	printf(" : r: %d g: %d b: %d\n", light->color.red, \
										light->color.green, \
										light->color.blue);
}

void	print_info_light(const t_light *light)
{
	while (light != NULL)
	{
		print_single_light(light);
		light = light->next;
	}
}

void	print_info_camera(const t_cam *cam)
{
	printf("[CAMERA]\n");
	printf("\tpos : [%3.4f, %3.4f, %3.4f]\n", cam->pos.x \
											, cam->pos.y \
											, cam->pos.z);
	printf("\tdir : [%3.4f, %3.4f, %3.4f]\n", cam->dir.x \
											, cam->dir.y \
											, cam->dir.z);
	printf("\tHFOV : %3.4f(rad)\n", cam->hfov);
	printf("\tHFOV : %3.4f(deg)\n", (cam->hfov) * (180 / M_PI));
}

void	print_info_scene(void)
{
	const t_scene	*scene = get_scene();
	const int		red = scene->ambient_color.red;
	const int		green = scene->ambient_color.green;
	const int		blue = scene->ambient_color.blue;

	print_info_light(scene->light);
	printf("[AMBIENT]\n");
	printf("\tratio : %3.4f\n", scene->ambient_ratio);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n", red, green, blue);
	print_info_camera(scene->cam);
	printf("[OBJECTS]\n");
	print_info_quads(scene->quads);
}
