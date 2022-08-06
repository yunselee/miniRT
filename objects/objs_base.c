#include "objects.h"

double intersect(t_ray ray, t_obj_base *obj, \
						unsigned int *pcolor)
{
	return obj->vtable_->obj_interstion(ray, obj, pcolor);
}

t_vec3	get_normal_vector(t_obj_base *obj, t_vec3 point, t_vec3 cam_pos)
{
	return obj->vtable_->obj_get_normal_vector(obj, point, cam_pos);
}
