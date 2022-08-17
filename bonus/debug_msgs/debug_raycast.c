/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:11:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/17 21:55:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "debug_msgs.h"
#include "print_info.h"
#include "scene_editer.h"

void	debug_single_ray_cast(const t_quadrics *Q, \
								const float *dist, \
								const t_vec3 *hit_point, \
								const t_color *color)
{
	t_vec3	point_from_obj;
	
	if (get_scene_editer()->debug == D_NONE)
		return;
	if (Q  && dist && !hit_point && !color)
	{
		printf("\ttarget obj info : \n");
		print_single_quadrics(Q);
		printf("intersecting distance : %f\n", *dist);
	}
	else if (!Q && !dist && hit_point && !color && (isnan(*dist) == FALSE))
	{
		point_from_obj = v3_sub(*hit_point, Q->org);
		printf("intersecting point from obj : [%f %f %f]\n", \
											point_from_obj.x, \
											point_from_obj.y, \
											point_from_obj.z);
	}
	else if (!Q && !dist && !hit_point && color)
		printf("\tfinal pixel color : \033[38;2;%d;%d;%dm◼︎(%d %d %d)\033[0m\n", \
							color->red, color->green, color->blue, \
							color->red, color->green, color->blue);
}

void	debug_phong_reflection(const t_vec3 *normal, const t_vec3 *point)
{
	if (get_scene_editer()->debug == D_NONE)
		return;
	if (normal && point)
	{
		printf("\t  hit point : [%f, %f, %f]\n", point->x, point->y, point->z);
		printf("\t    normal  : [%f, %f, %f]\n", normal->x, normal->y, normal->z);
	}
}