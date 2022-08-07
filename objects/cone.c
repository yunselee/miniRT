#include <math.h>
#include "libft.h"
#include "ray_cast.h"
#include "objects.h"
#include <stdio.h>

double	solve_quadratic_equation(double a, double b, double c);

static double	obj_interstion(t_ray ray, const t_obj_base *obj)
{
    //todo cos_squre into obj obj->r * M_PI / 180
    double cos_squre = pow(cos(obj->r * M_PI / 180), 2);
    t_vec3 op = v3_sub(ray.org, obj->o);
    double a = pow(v3_dot(obj->n, ray.dir), 2)\
                    - cos_squre;
    double b = 2 * (v3_dot(op, obj->n) * v3_dot(obj->n, ray.dir) \
                            - cos_squre * v3_dot(ray.dir, op));
    double c = pow(v3_dot(op, obj->n), 2) \
                    - cos_squre * v3_dot(op, op);

    return solve_quadratic_equation(a,b,c);  
}

/*
o_to_p : org_of_object to intersect point
cam_to_p : cam_position to intersect point
o_n : normal vector of object
TODO 안밖처처리리
*/
static t_vec3	obj_get_normal_vector(const t_obj_base *obj, t_vec3 point, \
									t_vec3 cam_pos)
{
    const t_vec3 op =  v3_sub(obj->o , point);
    const t_vec3 on = v3_mul(obj->n, 1/cos(obj->r));
    const t_vec3 normal = v3_normalize(v3_sub(op, on));
    cam_pos.x = cam_pos.x;

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
	printf("\ttype : CONE\n");
	printf("\torg : [%3.4f, %3.4f, %3.4f]\n", obj->o.x \
											, obj->o.y \
											, obj->o.z);
	printf("\tnormal : [%3.4f, %3.4f, %3.4f]\n", obj->n.x \
												, obj->n.y \
												, obj->n.z);
	printf("\tAngle : %3.4f\n", obj->r);
	printf("\t\033[38;2;%d;%d;%dmcolor\033[0m", red, green, blue);
	printf(" : r: %d g: %d b: %d\n\n", red, green, blue);
}


struct objs_vtable_ *get_cone()
{
	static struct objs_vtable_ cone[] = { { obj_interstion, obj_get_normal_vector, obj_print_info } };

	return cone;
}