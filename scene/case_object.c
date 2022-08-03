/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:41:42 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:23:35 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "../LIBFT/libft.h"
#include <stdlib.h>
#include <math.h>
#include "in_parsing.h"

static void	ft_addlst_back(t_object_base *objlst, t_object_base *node)
{
	t_object_base	*last;

	last = objlst;
	while (last->next)
		last = last->next;
	last->next = node;
	last->next->next = NULL;
}

void	free_objectlst(t_object_base *objlst)
{
	t_object_base	*curr;
	t_object_base	*next;

	curr = objlst;
	while (curr)
	{
		next = curr -> next;
		free(curr);
		curr = next;
	}
}

int	case_plane(t_scene *scene, char **single_scene)
{
	t_object_base	*new_obj;

	if (ft_strsetlen(single_scene) != 4)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_object_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_PLANE;
	if ((str_to_vec3(single_scene[1], &new_obj->org) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->normal) == FALSE) \
		|| (str_to_color(single_scene[3], &new_obj->color) == FALSE))
		return (FALSE);
	if (round(vec3_l2norm(new_obj->normal) * 10000) / 10000 != 1.0)
		return (FALSE);
	if (scene->obj == NULL)
		scene->obj = new_obj;
	else
		ft_addlst_back((scene->obj), new_obj);
	return (TRUE);
}

int	case_sphere(t_scene *scene, char **single_scene)
{
	t_object_base	*new_obj;

	if (ft_strsetlen(single_scene) != 4)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_object_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_SPHERE;
	if ((str_to_vec3(single_scene[1], &new_obj->org) == FALSE) \
		|| (ft_strtod(single_scene[2], &new_obj->radius) == FALSE) \
		|| (str_to_color(single_scene[3], &new_obj->color) == FALSE))
		return (FALSE);
	if (new_obj->radius <= 0.0)
		return (FALSE);
	new_obj->radius /= 2;
	if (scene->obj == NULL)
		scene->obj = new_obj;
	else
		ft_addlst_back((scene->obj), new_obj);
	new_obj->normal = create_vec3(0, 0, 0);
	return (TRUE);
}

int	case_cylinder(t_scene *scene, char **single_scene)
{
	t_object_base	*new_obj;

	if (ft_strsetlen(single_scene) != 6)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_object_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_CYLINDER;
	if ((str_to_vec3(single_scene[1], &new_obj->org) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->normal) == FALSE) \
		|| (ft_strtod(single_scene[3], &new_obj->radius) == FALSE) \
		|| (ft_strtod(single_scene[4], &new_obj->height) == FALSE)
		|| (str_to_color(single_scene[5], &new_obj->color) == FALSE))
		return (FALSE);
	if (round(vec3_l2norm(new_obj->normal) * 10000) / 10000 != 1.0)
		return (FALSE);
	if (new_obj->radius <= 0.0 || new_obj->height <= 0.0)
		return (FALSE);
	new_obj->radius /= 2;
	if (scene->obj == NULL)
		scene->obj = new_obj;
	else
		ft_addlst_back((scene->obj), new_obj);
	return (TRUE);
}
