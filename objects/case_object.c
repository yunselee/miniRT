/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:41:42 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 18:31:52 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>
#include "in_parsing.h"
#include "objects.h"

struct objs_vtable_ *get_cylinder();
struct objs_vtable_ *get_plain();
struct objs_vtable_ *get_sphere();
struct objs_vtable_ *get_cone();


static void	ft_addlst_back(t_obj_base **objlst, t_obj_base *node)
{
	t_obj_base	*last;

	node->next = NULL;
	if(*objlst == NULL)
	{
		*objlst = node;
		return ;
	}
	last = *objlst;
	while (last->next)
		last = last->next;
	last->next = node;
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

int	case_plane(t_scene *out_scene, char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 4)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_PLANE;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->n) == FALSE) \
		|| (str_to_color(single_scene[3], &new_obj->color) == FALSE))
		return (FALSE);
	if (round(v3_l2norm(new_obj->n) * 10000) / 10000 != 1.0)
		return (FALSE);
	ft_addlst_back(&(out_scene->obj), new_obj);
	new_obj->vtable_ = get_plain();
	return (TRUE);
}

int	case_sphere(t_scene *out_scene, char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 4)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_SPHERE;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (ft_strtod(single_scene[2], &new_obj->r) == FALSE) \
		|| (str_to_color(single_scene[3], &new_obj->color) == FALSE))
		return (FALSE);
	if (new_obj->r <= 0.0)
		return (FALSE);
	new_obj->r /= 2;
	ft_addlst_back(&(out_scene->obj), new_obj);
	new_obj->n = make_v3(0, 0, 0);
	new_obj->vtable_ = get_sphere();
	return (TRUE);
}

int	case_cylinder(t_scene *out_scene, char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 6)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_CYLINDER;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->n) == FALSE) \
		|| (ft_strtod(single_scene[3], &new_obj->r) == FALSE) \
		|| (ft_strtod(single_scene[4], &new_obj->h) == FALSE)
		|| (str_to_color(single_scene[5], &new_obj->color) == FALSE))
		return (FALSE);
	if (round(v3_l2norm(new_obj->n) * 10000) / 10000 != 1.0)
		return (FALSE);
	if (new_obj->r <= 0.0 || new_obj->h <= 0.0)
		return (FALSE);
	new_obj->r /= 2;
	ft_addlst_back(&(out_scene->obj), new_obj);
	new_obj->vtable_ = get_cylinder();
	return (TRUE);
}

// cone
/*
∗ identifier: co
co 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
∗ x,y,z coordinates: 50.0,0.0,20.6
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
r : 0~180
∗ R,G,B colors in range [0,255]: 10, 0, 255

*/
int case_cone(t_scene *out_scene, char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 5)
		return (FALSE);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (FALSE);
	new_obj->type = E_CONE;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->n) == FALSE) \
		|| (ft_strtod(single_scene[3], &new_obj->r) == FALSE) \
		|| (str_to_color(single_scene[4], &new_obj->color) == FALSE))
		return (FALSE);
	if (round(v3_l2norm(new_obj->n) * 10000) / 10000 != 1.0)
		return (FALSE);
	if (new_obj->r <= 0.0)
		return (FALSE);
	ft_addlst_back(&(out_scene->obj), new_obj);
	new_obj->vtable_ = get_cone();
	return (TRUE);

}