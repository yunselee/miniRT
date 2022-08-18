/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:11:01 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/18 14:57:48 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "scene.h"
#include "in_parsing.h"
#include "resolution.h"

int	case_camera(t_scene *scene, char **single_scene)
{
	if (scene->cam != NULL)
		return (FALSE);
	if (ft_strsetlen(single_scene) != 4)
		return (FALSE);
	scene->cam = malloc(sizeof(t_cam));
	if (!scene->cam)
		return (FALSE);
	if (str_to_vec3(single_scene[1], &(scene->cam->pos)) == FALSE \
		|| str_to_vec3(single_scene[2], &(scene->cam->dir)) == FALSE \
		|| ft_strtof(single_scene[3], &(scene->cam->hfov)) == FALSE)
		return (FALSE);
	if (v3_l2norm(scene->cam->dir) > 1.001 \
		|| v3_l2norm(scene->cam->dir) < 0.999)
		return (FALSE);
	if (scene->cam->hfov <= 0 || scene->cam->hfov >= 180)
		return (FALSE);
	scene->cam->hfov = scene->cam->hfov * M_PI / 180;
	scene->cam->cam_proportion = (WIN_WIDTH / 2) / \
								tan(get_scene()->cam->hfov / 2);
	return (TRUE);
}
