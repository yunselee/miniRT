/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:47:27 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/10 19:31:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "ray_cast.h"
#include "objects.h"

static double	obj_interstion(t_ray ray, \
								const t_obj_base *obj)
{
	const t_vec3	obj_org  = v3_sub(obj->o, ray.org);;
	double	dist;

	if (v3_dot(ray.dir, obj->n) == 0)
		return (NAN);
	dist = v3_dot(obj_org, obj->n) / v3_dot(ray.dir, obj->n);
	if (dist <= 0)
		return (NAN);
	return (dist);
}

static void	obj_print_info(const t_obj_base *obj)
{
	const int	red = obj->color.red;
	const int	green = obj->color.green;
	const int	blue = obj->color.blue;

	printf("\ttype : PLANE\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->o.x \
											, obj->o.y \
											, obj->o.z);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", obj->n.x \
												, obj->n.y \
												, obj->n.z);
	printf("\ttangential : [%3.4f, %3.4f, %3.4f]\n", obj->tangential.x \
												, obj->tangential.y \
												, obj->tangential.z);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n", red, green, blue);
	printf("\tspecular factors : Rs : %.2f alpha : %d\n\n", obj->rs, obj->alpha);
}

t_vec3	plain_get_normal_vector(const t_obj_base *obj, \
											t_vec3 point, t_vec3 cam_pos)
{
	const t_vec3	org_to_cam = v3_sub(cam_pos, obj->o);

	point.x = point.x;
	if (v3_dot(org_to_cam, obj->n) > 0)
		return (obj->n);
	else
		return (v3_mul(obj->n, -1));
}

struct s_obj_vtable_	*get_plain(void)
{
	static struct s_obj_vtable_	plain[4];

	plain->obj_interstion = obj_interstion;
	plain->obj_print_info = obj_print_info;
	return (plain);
}
