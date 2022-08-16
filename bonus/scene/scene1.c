/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 05:05:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 09:20:47 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "scene.h"
#include "in_parsing.h"
#include "quadrics.h"

void	scene_destroy(void)
{
	t_scene	*scene;

	scene = get_scene();
	free(scene->cam);
	free_lightlst(scene->light);
	free_quadlist(scene->quads);
}

t_scene	*get_scene(void)
{
	static t_scene	scene;

	return (&scene);
}
