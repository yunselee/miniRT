/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:41:21 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:04:06 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"
#include <stdio.h>

static t_vec3 get_plane_normal(t_object_base *obj, t_vec3 cam_pos);
static t_vec3 get_sphere_normal(t_object_base *obj, t_vec3 intersection, t_vec3 cam_pos);
static t_vec3 get_cylinder_normal(t_object_base *obj, t_vec3 intersection, t_vec3 cam_pos);

t_vec3 get_normal_vector(t_object_base *obj, t_vec3 intersection , t_vec3 cam_pos)
{
	if (obj->type == E_PLANE)
		return (get_plane_normal(obj, cam_pos));
	else if (obj->type == E_SPHERE)
		return (get_sphere_normal(obj, intersection, cam_pos));
	else if (obj->type == E_CYLINDER)
		return (vec3_normalize(get_cylinder_normal(obj, intersection, cam_pos)));
	return (create_vec3(0, 0, 0));
}

static t_vec3 get_plane_normal(t_object_base *obj, t_vec3 cam_pos)
{
	t_vec3	org_to_cam;

	org_to_cam = vec3_subtract(cam_pos, obj->org);
	if (vec3_dot(org_to_cam, obj->normal) > 0)
		return (obj->normal);
	else
		return (vec3_scale(obj->normal, -1));
}

static t_vec3 get_sphere_normal(t_object_base *obj, t_vec3 intersection, t_vec3 cam_pos)
{
	t_vec3	normal;

	normal = vec3_normalize(vec3_subtract(intersection, obj->org));
	if (vec3_l2norm(vec3_subtract(cam_pos, obj->org)) < obj->radius)
		return (vec3_scale(normal, -1));
	return (normal);
}


static t_vec3 get_cylinder_normal(t_object_base *obj, t_vec3 intersection, t_vec3 cam_pos)
{
	t_vec3	org_to_intersection;
	t_vec3	cam_to_intersection;
	t_vec3	normal;

	cam_to_intersection = vec3_subtract(intersection, cam_pos);
	org_to_intersection = vec3_subtract(intersection, obj->org);
	if (vec3_dot(org_to_intersection, obj->normal) <= 0.00001 && \
		vec3_dot(org_to_intersection, obj->normal) >= -0.00001)
	{
		normal = obj->normal;
		if (vec3_dot(obj->normal, cam_to_intersection) > 0)
			normal = vec3_scale(normal, -1);
		return (normal);
	}
	org_to_intersection = vec3_subtract(intersection, vec3_add(obj->org, vec3_scale(obj->normal, obj->height)));
	if (vec3_dot(org_to_intersection, obj->normal) <= 0.00001 && \
		vec3_dot(org_to_intersection, obj->normal) >= -0.00001)
	{
		normal = obj->normal;
		if (vec3_dot(obj->normal, cam_to_intersection) > 0)
			normal = vec3_scale(normal, -1);
		return (normal);
	}
	normal = vec3_cross(obj->normal, vec3_cross(org_to_intersection, obj->normal));
	normal = vec3_normalize(normal);
	if (vec3_l2norm(vec3_cross(obj->normal, \
		vec3_cross((vec3_subtract(cam_pos, obj->org)), obj->normal))) < obj->radius)
		normal = vec3_scale(normal, -1);
	return (normal);
}