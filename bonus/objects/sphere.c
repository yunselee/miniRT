/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:58:54 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/10 22:54:58 by dkim2            ###   ########.fr       */
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
	const int	red = obj->color.red;
	const int	green = obj->color.green;
	const int	blue = obj->color.blue;

	printf("\ttype : SPHERE\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->o.x \
											, obj->o.y \
											, obj->o.z);
	printf("\tradius : %3.4f\n", obj->r);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", obj->n.x \
												, obj->n.y \
												, obj->n.z);
	printf("\ttangential : [%3.4f, %3.4f, %3.4f]\n", obj->tangential.x \
												, obj->tangential.y \
												, obj->tangential.z);
	printf ("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n", red, green, blue);
	printf("\tspecular factors : Rs : %.2f alpha : %d\n\n", obj->rs, obj->ns);
}

struct s_obj_vtable_	*get_sphere(void)
{
	static struct s_obj_vtable_	sphere[4];

	sphere->obj_interstion = obj_interstion;
	sphere->obj_print_info = obj_print_info;
	return (sphere);
}
