/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:20:20 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/10 15:07:53 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_vec3	cone_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
									t_vec3 cam_pos);
t_vec3	cylinder_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
									t_vec3 cam_pos);
t_vec3	plain_get_normal_vector(const t_obj_base *obj, \
											t_vec3 point, t_vec3 cam_pos);
t_vec3	sphere_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
								t_vec3 cam_pos);

double	intersect(t_ray ray, const t_obj_base *obj)
{
	return (obj->vtable_->obj_interstion(ray, obj));
}

t_vec3	get_normal_vector(const t_obj_base *obj, t_vec3 point, t_vec3 cam_pos)
{
	const t_vec3	a = {0, 0, 0, 0};

	if (obj->type == E_CONE)
		return (cone_get_normal_vector(obj, point, cam_pos));
	if (obj->type == E_PLAIN)
		return (plain_get_normal_vector(obj, point, cam_pos));
	if (obj->type == E_SPHERE)
		return (sphere_get_normal_vector(obj, point, cam_pos));
	if (obj->type == E_CYLINDER)
		return (cylinder_get_normal_vector(obj, point, cam_pos));
	return (a);
}

// wrapper function
void	print_info(const t_obj_base *obj)
{
	obj->vtable_->obj_print_info(obj);
}
