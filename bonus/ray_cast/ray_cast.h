/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:07:19 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/17 16:36:13 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H
# include "scene.h"
# include "quadrics.h"
# include "mlx_manager.h"
# include "vector3.h"
# include "color.h"

typedef struct s_thread_local_object
{
	int		x;
	int		y;
}			t_thread_local_object;

float	get_intersect_distance(t_quadrics *objlst, \
								t_quadrics **intersecting_obj_out, \
								t_ray ray);

void	render_lightsource(double depth);

t_color	single_ray_cast(t_mlx *mlx, t_ray ray);

t_color	phong_reflection(t_quadrics *hit_obj, \
							t_vec3 intersection, \
							t_vec3 view_point);

t_color	diffuse_light(const t_scene *scene, \
						t_quadrics *hit_obj, \
						t_vec3 normal, \
						t_vec3 intersection);

t_color	specular_light(const t_scene *scene, \
					t_quadrics *hit_obj, \
					t_vec3 mirror_ray, \
					t_vec3 intersection);

void	*thread_routine(void *ptr);

#endif