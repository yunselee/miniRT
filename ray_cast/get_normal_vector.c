/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:41:21 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 18:33:09 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"
#include <stdio.h>

static t_vec3	get_plane_normal(t_obj_base *O, t_vec3 P);
static t_vec3	get_sphere_normal(t_obj_base *O, t_vec3 I, t_vec3 P);
static t_vec3	get_cylinder_normal(t_obj_base *O, t_vec3 I, t_vec3 P);

t_vec3	get_normal_vector(t_obj_base *obj, t_vec3 point, t_vec3 cam_pos)
{
	if (obj->type == E_PLANE)
		return (get_plane_normal(obj, cam_pos));
	else if (obj->type == E_SPHERE)
		return (get_sphere_normal(obj, point, cam_pos));
	else if (obj->type == E_CYLINDER)
		return (v3_normalize(get_cylinder_normal(obj, point, cam_pos)));
	return (make_v3(0, 0, 0));
}

static t_vec3	get_plane_normal(t_obj_base *obj, t_vec3 cam_pos)
{
	t_vec3	org_to_cam;

	org_to_cam = v3_sub(cam_pos, obj->o);
	if (v3_dot(org_to_cam, obj->n) > 0)
		return (obj->n);
	else
		return (v3_mul(obj->n, -1));
}

static t_vec3	get_sphere_normal(t_obj_base *obj, t_vec3 point, \
								t_vec3 cam_pos)
{
	t_vec3	normal;

	normal = v3_normalize(v3_sub(point, obj->o));
	if (v3_l2norm(v3_sub(cam_pos, obj->o)) < obj->r)
		return (v3_mul(normal, -1));
	return (normal);
}

/*
o_to_p : org_of_object to intersect point
cam_to_p : cam_position to intersect point
o_n : normal vector of object
*/
static t_vec3	get_cylinder_normal(t_obj_base *obj, t_vec3 point, \
									t_vec3 cam_pos)
{
	t_vec3	o_to_p;
	t_vec3	cam_to_p;
	t_vec3	normal;
	t_vec3	o_n;

	o_n = obj->n;
	cam_to_p = v3_sub(point, cam_pos);
	o_to_p = v3_sub(point, obj->o);
	if (v3_dot(o_to_p, o_n) <= EPSILON && v3_dot(o_to_p, o_n) >= -EPSILON)
	{
		if (v3_dot(o_n, cam_to_p) > 0)
			return (v3_mul(o_n, -1));
		return (o_n);
	}
	o_to_p = v3_sub(point, v3_add(obj->o, v3_mul(o_n, obj->h)));
	if (v3_dot(o_to_p, o_n) <= EPSILON && v3_dot(o_to_p, o_n) >= -EPSILON)
	{
		if (v3_dot(o_n, cam_to_p) > 0)
			return (v3_mul(o_n, -1));
		return (o_n);
	}
	normal = v3_normalize(v3_crs(o_n, v3_crs(o_to_p, o_n)));
	if (v3_l2norm(v3_crs(o_n, v3_crs((v3_sub(cam_pos, obj->o)), o_n))) < obj->r)
		normal = v3_mul(normal, -1);
	return (normal);
}
