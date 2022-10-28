/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:07:19 by dkim2             #+#    #+#             */
/*   Updated: 2022/10/28 11:32:24 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H
# include "scene.h"
# include "quadrics.h"
# include "mlx_manager.h"
# include "vector3.h"
# include "color.h"

# define RECURSE (3)
# define THREAD_PARAM (3)
# define THREAD_NUM (THREAD_PARAM * THREAD_PARAM)


typedef struct s_thread_local_object
{
	int	x;
	int	y;
}	t_thread_local_object;

typedef struct s_arg
{
	t_quadrics	*h_ob;
	t_vec3		normal;
	t_vec3		hit_point;
	t_vec3		mirror_ray;
}	t_arg;

void	ray_cast(void);

float	get_intersect_distance(t_quadrics *objlst, \
								t_quadrics **intersecting_obj_out, \
								t_ray ray);

void	render_lightsource(double depth);

t_color	single_ray_cast(t_ray ray, int recurse);

t_color	phong_reflection(t_quadrics *hit_obj, \
							t_vec3 intersection, \
							t_vec3 view_point, \
							int recurse);
void	*thread_routine(void *ptr);

t_color	diffuse_specular(t_arg *a, int recurse);

#endif