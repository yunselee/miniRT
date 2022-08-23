/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:11:03 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/23 20:06:08 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"
#include <stdlib.h>
#include "in_parsing.h"

t_light	*create_light(t_vec3 pos, double b)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->o.x = pos.x;
	light->o.y = pos.y;
	light->o.z = pos.z;
	light->bright = b;
	return (light);
}

int	case_light(t_scene *scene, char **single_scene)
{
	t_vec3	pos;
	double	brightness;

	if (scene->light != NULL)
		return (FALSE);
	if (ft_strsetlen(single_scene) != 3 && ft_strsetlen(single_scene) != 4)
		return (FALSE);
	if (str_to_vec3(single_scene[1], &pos) == FALSE)
		return (FALSE);
	if (ft_strtod(single_scene[2], &brightness) == FALSE)
		return (FALSE);
	if (brightness < 0.0 || brightness > 1.0)
		return (FALSE);
	scene->light = create_light(pos, brightness);
	if (scene->light == NULL)
		return (FALSE);
	if (str_to_color(single_scene[3], &(scene->light->color)) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	case_ambient(t_scene *scene, char **single_scene)
{
	if (scene->ambient_ratio != 0.0)
		return (FALSE);
	if (ft_strsetlen(single_scene) != 3)
		return (FALSE);
	if (scene->ambient_ratio != 0)
		return (FALSE);
	if (ft_strtod(single_scene[1], &(scene->ambient_ratio)) == FALSE)
		return (FALSE);
	if (scene->ambient_ratio <= 0.0 || scene->ambient_ratio > 1.0)
		return (FALSE);
	if (str_to_color(single_scene[2], &(scene->ambient_color)) == FALSE)
		return (FALSE);
	return (TRUE);
}
