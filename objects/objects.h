#ifndef OBJECTS_H
# define OBJECTS_H

#include "vector3.h"
#include "color.h"

enum e_type
{
	E_PLANE = 0,
	E_SPHERE,
	E_CYLINDER
};

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}	t_ray;


typedef struct s_object_base
{
	enum e_type				type;
	t_color					color;
	double					r;
	double					h;
	t_vec3					o;
	t_vec3					n;
	struct s_object_base	*next;
	const struct objs_vtable_ *vtable_;
}				t_obj_base;

typedef struct s_scene	t_scene;


struct objs_vtable_
{
	double (*obj_interstion)(t_ray ray, const t_obj_base *obj, \
						unsigned int *out_color);
	t_vec3	(*obj_get_normal_vector)(const t_obj_base *obj, t_vec3 point, t_vec3 cam_pos);
};


// wrapper function
double intersect(t_ray ray, const t_obj_base *obj, unsigned int *out_color);
// wrapper function
t_vec3	get_normal_vector(const t_obj_base *obj, t_vec3 point, t_vec3 cam_pos);

int init_object(t_scene *out_scene, char **single_scene);
void	free_objectlst(t_obj_base *objlst);

#endif