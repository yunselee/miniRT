/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:58:54 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/08 19:55:13 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "ray_cast.h"
#include "objects.h"

double	solve_quadratic_equation(double a, double b, double c);

static double	obj_interstion(t_ray ray, \
								const t_obj_base *obj)
{
	const t_vec3	obj_org = v3_sub(obj->o, ray.org);
	const double	distance = solve_quadratic_equation(\
					v3_dot(ray.dir, ray.dir), \
					-2 * v3_dot(obj_org, ray.dir), \
					v3_dot(obj_org, obj_org) - pow(obj->r, 2));

	if (distance == NAN)
		return (NAN);
	return (distance);
}

t_vec3	sphere_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
								t_vec3 cam_pos)
{
	const t_vec3	normal = v3_normalize(v3_sub(point, obj->o));

	if (v3_l2norm(v3_sub(cam_pos, obj->o)) < obj->r)
		return (v3_mul(normal, -1));
	return (normal);
}

static void	obj_print_info(const t_obj_base *obj)
{
	int	red;
	int	green;
	int	blue;

	red = obj->color.red;
	green = obj->color.green;
	blue = obj->color.blue;
	printf("\ttype : SPHERE\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->o.x \
											, obj->o.y \
											, obj->o.z);
	printf("\tradius : %3.4f\n", obj->r);
	printf ("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n\n", red, green, blue);
}

struct s_obj_vtable_	*get_sphere(void)
{
	static struct s_obj_vtable_	sphere[5];

	sphere->obj_interstion = obj_interstion;
	sphere->obj_print_info = obj_print_info;
	return (sphere);
}
