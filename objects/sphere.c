#include <math.h>
#include "libft.h"
#include "ray_cast.h"
#include "objects.h"

// discriminant : 이차방정식의 판별식
double	solve_quadratic_equation(double a, double b, double c)
{
	double	solution;
	double	discriminant;

	if (a < 0)
	{
		a = -a;
		b = -b;
		c = -c;
	}
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		solution = -1;
	else if (discriminant == 0)
		solution = -b / (2 * a);
	else
	{
		solution = -b - sqrt(discriminant);
		if (solution <= 0)
			solution = -b + sqrt(discriminant);
	}
	if (solution <= 0)
		return (NAN);
	return (solution / (2 * a));
}

static double	obj_interstion(t_ray ray, \
								const t_obj_base *obj)
{
	const t_vec3	obj_org = v3_sub(obj->o, ray.org);;
	const double	distance = solve_quadratic_equation( \
					v3_dot(ray.dir, ray.dir), \
					-2 * v3_dot(obj_org, ray.dir), \
					v3_dot(obj_org, obj_org) - pow(obj->r, 2));
	
	if (distance == NAN)
		return (NAN);
	return (distance);
}

static t_vec3	obj_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
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

struct objs_vtable_ *get_sphere()
{
	static struct objs_vtable_ sphere[] = { { obj_interstion, obj_get_normal_vector, obj_print_info} };

	return sphere;
}
