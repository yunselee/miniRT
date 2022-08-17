/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:06:37 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/17 21:47:32 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MSGS_H
# define DEBUG_MSGS_H
# include "mlx_part.h"
# include "quadrics.h"

typedef enum e_debugmode
{
	D_NONE = 0,
	D_SIMPLE,
	D_DETAIL
}	t_debug_mode;

/* QUADRICS */
void	debug_find_intersection(const t_quadrics *Q, \
									const t_ray *ray);

void	debug_z_range(const float zrange[2], \
						const float *sol, \
						const float *z);

void	debug_solve_equation(const float coefs[3], \
							const float *D, \
							const float *sol1, \
							const float *sol2);
/* RAY CASTING */
void	debug_single_ray_cast(const t_quadrics *Q, \
								const float *dist, \
								const t_vec3 *hit_point, \
								const t_color *color);

void	debug_phong_reflection(const t_vec3 *normal, const t_vec3 *point);

/* REFLECTION */
void	debug_light(const t_light *light);

void	debug_color(const t_color *color);

void	debug_ambient(const t_quadrics *Q);

void	debug_diffuse(const float *to_obj, \
						const float *to_light,\
						const float *diffuse);

void	debug_specular(const float *to_obj, \
						const float *to_light, \
						const float *specular);

# endif