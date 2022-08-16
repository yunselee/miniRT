/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 12:54:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_H
# define QUADRICS_H
# include "quadrics_type.h"
# include "scene_type.h"
# include "ray_cast.h"

typedef struct s_float_sol
{
	float	sol1;
	float	sol2;
}			t_sols;

int			init_quadrics(t_scene *outscene, char **singlescene);
void		free_quadlist(t_quadrics *quad_list);

t_quadrics	*case_quad_plane(char **single_scene);
t_quadrics	*case_quad_sphere(char **single_scene);
t_quadrics	*case_quadrics(char **single_scene);
void		rotate_quadrics(t_quadrics *Q, t_vec3 axis, float deg);

void		rotate_to_quad_dir(t_quadrics *Q);
float		find_intersection(const t_quadrics *Q, const t_ray *R);
t_vec3		quad_normal_vector(const t_quadrics *Q, t_vec4 p, t_vec4 viewpnt);

#endif