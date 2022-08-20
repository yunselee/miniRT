/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:07:04 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/19 14:00:29 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "debug_msgs.h"
#include "print_info.h"
#include "scene_editer.h"

void	debug_light(const t_light *light)
{
	if (get_scene_editer()->debug == D_NONE)
		return ;
	if (light)
	{
		printf("\t  current light source: \n");
		print_single_light(light);
	}
}

void	debug_color(const t_color *color)
{
	if (get_scene_editer()->debug == D_NONE)
		return ;
	else if (color)
		printf("\tcolor :\033[38;2;%d;%d;%dm◉(%d, %d, %d)\033[0m\n", \
			color->red, color->green, color->blue, \
			color->red, color->green, color->blue);
}

void	debug_ambient(const t_quadrics *Q)
{
	if (get_scene_editer()->debug == D_NONE)
		return ;
	if (Q)
	{
		printf("\t  target object :\n");
		print_single_quadrics(Q);
	}
	else
		printf("\t--<AMBIENT LIGHTING>--\n");
}

void	debug_diffuse(const float *to_obj, \
						const float *to_light, \
						const float *diffuse)
{
	if (get_scene_editer()->debug == D_NONE)
		return ;
	if (to_obj && to_light && !diffuse)
	{
		printf("\t  shortest intersecting distance : %f\n", *to_obj);
		printf("\t  distance to light source : %f\n", *to_light);
		if (*to_obj < *to_light)
			printf("\t  the light source is blocked\n");
	}
	else if (!to_obj && !to_light && diffuse)
		printf("\tdiffuse : %f\n", *diffuse);
	else if (!to_obj && !to_light && !diffuse)
		printf("\n\t--<DIFFUSE LIGHTING>--\n");
}

void	debug_specular(const int *recurse,
						const float *to_obj, \
						const float *to_light, \
						const float *specular)
{
	if (get_scene_editer()->debug == D_NONE)
		return ;
	if (!recurse && to_obj && to_light && !specular)
	{
		printf("\t  shortest intersecting distance : %f\n", *to_obj);
		printf("\t  distance to light source : %f\n", *to_light);
		if (*to_obj < *to_light)
			printf("\t  the light source is blocked\n");
	}
	else if (!recurse && !to_obj && !to_light && specular)
		printf("\tspecular : %f\n", *specular);
	else if (recurse && !to_obj && !to_light && !specular)
		printf("\n\t--<SPECULAR LIGHTING>--\n\trecurse : %d\n", *recurse);
}
