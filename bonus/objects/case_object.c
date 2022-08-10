/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:41:42 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/10 22:54:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>
#include "in_parsing.h"
#include "objects.h"

struct s_obj_vtable_	*get_cylinder(void);
struct s_obj_vtable_	*get_plain(void);
struct s_obj_vtable_	*get_sphere(void);
struct s_obj_vtable_	*get_cone(void);

t_obj_base	*case_plane(char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 6)
		return (NULL);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (NULL);
	new_obj->type = E_PLAIN;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->n) == FALSE) \
		|| (str_to_color(single_scene[3], &new_obj->color) == FALSE) \
		|| (ft_strtod(single_scene[4], &new_obj->rs) == FALSE) \
		|| (ft_strtoi(single_scene[5], &new_obj->ns) == FALSE))
	{
		free(new_obj);
		return (NULL);
	}
	new_obj->vtable_ = get_plain();
	return (new_obj);
}

t_obj_base	*case_sphere(char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 6)
		return (NULL);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (NULL);
	new_obj->type = E_SPHERE;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (ft_strtod(single_scene[2], &new_obj->r) == FALSE) \
		|| (str_to_color(single_scene[3], &new_obj->color) == FALSE) \
		|| (ft_strtod(single_scene[4], &new_obj->rs) == FALSE) \
		|| (ft_strtoi(single_scene[5], &new_obj->ns) == FALSE) \
		|| (new_obj->r <= 0.0))
	{
		free(new_obj);
		return (NULL);
	}
	new_obj->r /= 2;
	new_obj->n = make_v3(0, 0, 1);
	new_obj->vtable_ = get_sphere();
	return (new_obj);
}

t_obj_base	*case_cylinder(char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 8)
		return (NULL);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (NULL);
	new_obj->type = E_CYLINDER;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->n) == FALSE) \
		|| (ft_strtod(single_scene[3], &new_obj->r) == FALSE) \
		|| (ft_strtod(single_scene[4], &new_obj->h) == FALSE) \
		|| (str_to_color(single_scene[5], &new_obj->color) == FALSE) \
		|| (ft_strtod(single_scene[6], &new_obj->rs) == FALSE) \
		|| (ft_strtoi(single_scene[7], &new_obj->ns) == FALSE) \
		|| (new_obj->r <= 0.0 || new_obj->h <= 0.0))
	{
		free(new_obj);
		return (NULL);
	}
	new_obj->r /= 2;
	new_obj->tangential = get_tangential(&(new_obj->n));
	new_obj->vtable_ = get_cylinder();
	return (new_obj);
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
t_obj_base	*case_cone(char **single_scene)
{
	t_obj_base	*new_obj;

	if (ft_strsetlen(single_scene) != 7)
		return (NULL);
	new_obj = ft_calloc(1, sizeof(t_obj_base));
	if (!new_obj)
		return (NULL);
	new_obj->type = E_CONE;
	if ((str_to_vec3(single_scene[1], &new_obj->o) == FALSE) \
		|| (str_to_vec3(single_scene[2], &new_obj->n) == FALSE) \
		|| (ft_strtod(single_scene[3], &new_obj->r) == FALSE) \
		|| (str_to_color(single_scene[4], &new_obj->color) == FALSE) \
		|| (ft_strtod(single_scene[5], &new_obj->rs) == FALSE) \
		|| (ft_strtoi(single_scene[6], &new_obj->ns) == FALSE) \
		|| new_obj->r <= 0.0)
	{
		free(new_obj);
		return (NULL);
	}
	new_obj->vtable_ = get_cone();
	return (new_obj);
}
