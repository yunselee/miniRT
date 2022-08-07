#include "objects.h"

double intersect(t_ray ray, const t_obj_base *obj)
{
	return obj->vtable_->obj_interstion(ray, obj);
}

t_vec3	get_normal_vector(const t_obj_base *obj, t_vec3 point, t_vec3 cam_pos)
{
	return obj->vtable_->obj_get_normal_vector(obj, point, cam_pos);
}

// wrapper function
void print_info(const t_obj_base *obj)
{
	obj->vtable_->obj_print_info(obj);
}
