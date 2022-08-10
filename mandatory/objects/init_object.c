/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:59:19 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/08 19:56:47 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"
#include "libft.h"
#include <stdlib.h>

int	case_plane(t_scene *scene, char **single_scene);
int	case_sphere(t_scene *scene, char **single_scene);
int	case_cylinder(t_scene *scene, char **single_scene);
int	case_cone(t_scene *out_scene, char **single_scene);

int	init_object(t_scene *out_scene, char **single_scene)
{
	int	res;

	res = FALSE;
	if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		res = case_sphere(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		res = case_plane(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "cy", 3) == 0)
		res = case_cylinder(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "co", 3) == 0)
		res = case_cone(out_scene, single_scene);
	return (res);
}

void	free_objectlst(t_obj_base *out_objlst)
{
	t_obj_base	*curr;
	t_obj_base	*next;

	curr = out_objlst;
	while (curr)
	{
		next = curr -> next;
		free(curr);
		curr = next;
	}
}
