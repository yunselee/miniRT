/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:07:19 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 16:27:03 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H
# include "scene.h"
# include "mlx_part.h"
# include "vector3.h"
# include "color.h"
# include "quadrics.h"

float	get_intersect_distance(t_quadrics *objlst, \
								t_quadrics **intersecting_obj_out, \
								t_ray ray);

void	render_lightsource(t_mlx *mlx, double depth);

t_color	single_ray_cast(t_mlx *mlx, t_ray ray);

void	ray_cast(t_mlx *mlx);

t_color	phong_reflection(t_mlx *mlx, \
							t_quadrics *hit_obj, \
							t_vec3 intersection, \
							t_vec3 view_point);

t_color	diffuse_light(t_scene *scene, \
						t_quadrics *hit_obj, \
						t_vec3 normal, \
						t_vec3 intersection);

t_color	specular_light(t_scene *scene, \
					t_quadrics *hit_obj, \
					t_vec3 mirror_ray, \
					t_vec3 intersection);

#endif