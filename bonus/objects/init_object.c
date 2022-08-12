/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:59:19 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/10 22:54:55 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "objects.h"
#include "scene.h"
#include "libft.h"

t_obj_base	*case_plane(char **single_scene);
t_obj_base	*case_sphere(char **single_scene);
t_obj_base	*case_cylinder(char **single_scene);
t_obj_base	*case_cone(char **single_scene);

static void	ft_addlst_back(t_obj_base **objlst, t_obj_base *node)
{
	t_obj_base	*last;

	node->next = NULL;
	if (*objlst == NULL)
	{
		*objlst = node;
		return ;
	}
	last = *objlst;
	while (last->next)
		last = last->next;
	last->next = node;
}

int	init_object(t_scene *out_scene, char **single_scene)
{
	int			res;
	t_obj_base	*obj;

	res = FALSE;
	if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		obj = case_sphere(single_scene);
	else if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		obj = case_plane(single_scene);
	else if (ft_strncmp(single_scene[0], "cy", 3) == 0)
		obj = case_cylinder(single_scene);
	else if (ft_strncmp(single_scene[0], "co", 3) == 0)
		obj = case_cone(single_scene);
	else
		return (res);
	if ((obj == NULL) \
		|| round(v3_l2norm(obj->n) * 10000) / 10000 != 1.0
		|| obj->rs < 0 || obj->rs >= 1 || obj->ns <= 1)
	{
		free(obj);
		return (FALSE);
	}
	obj->tangential = get_tangential(&(obj->n));
	ft_addlst_back(&(out_scene->obj), obj);
	return (TRUE);
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
