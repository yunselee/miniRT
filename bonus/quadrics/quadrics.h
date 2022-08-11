/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 22:18:54 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_H
# define QUADRICS_H
# include "scene.h"
# include "color.h"
# include "matrix44.h"
# include "ray_cast.h"

typedef enum e_qtype
{
	Q_PLANE = 0,
	Q_QUADRICS
}	t_qtype;
struct quadrics
{
	t_qtype	type;
	t_mat44	coefs;
	t_vec4	org;
	t_vec4	dir;
	t_vec4	tan;
	t_color	color;
	float	spec_rs;
	int		spec_ns;
	float	range_z[2];
	struct quadrics	*next;
};

typedef	struct s_float_sol
{
	float	sol1;
	float	sol2;
}			t_sols;

int			init_quadrics(t_scene *outscene, char **singlescene);
void		free_quadlist(t_quadrics *quad_list);
t_quadrics	*case_quad_plane(char **single_scene);
t_quadrics	*case_quad_sphere(char **single_scene);
t_quadrics	*case_quadrics(char **single_scene);

float	find_intersection(const t_quadrics *Q, const t_ray *R);
t_vec3	quad_normal_vector(const t_quadrics *Q, t_vec4 point, t_vec4 viewpoint);


#endif