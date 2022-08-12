/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:00:49 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/10 16:43:35 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector3.h"
# include "color.h"

enum e_type
{
	E_PLAIN = 0,
	E_SPHERE,
	E_CYLINDER,
	E_CONE
};

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}	t_ray;

typedef struct s_object_base
{
	t_vec3						o;
	t_vec3						n;
	t_vec3						tangential;
	double						r;
	double						h;
	double						rs;
	t_color						color;
	enum e_type					type;
	int							alpha;
	struct s_object_base		*next;
	const struct s_obj_vtable_	*vtable_;
}				t_obj_base;

typedef struct s_scene	t_scene;

struct s_obj_vtable_
{
	double	(*obj_interstion)(t_ray ray, const t_obj_base *obj);
	void	(*obj_print_info)(const t_obj_base *obj);
};

t_vec3	get_tangential(const t_vec3 *unit_normal);

// wrapper function
double	intersect(t_ray ray, const t_obj_base *obj);
// wrapper function
t_vec3	get_normal_vector(const t_obj_base *obj, t_vec3 point, t_vec3 cam_pos);
// wrapper function
void	print_info(const t_obj_base *obj);

int		init_object(t_scene *out_scene, char **single_scene);

void	free_objectlst(t_obj_base *objlst);

#endif