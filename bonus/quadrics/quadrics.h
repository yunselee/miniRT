/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/10/28 11:02:18 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_H
# define QUADRICS_H
# include "matrix44.h"
# include "color.h"
# include "scene.h"
# include "mlx_manager.h"

typedef enum e_qtype
{
	Q_PLANE = 0,
	Q_QUADRICS
}	t_qtype;

typedef enum e_texturetype
{
	T_NORMAL = 0,
	T_TEXTURE,
}	t_texturetype;

typedef struct s_quadrics
{
	t_mat44				coefs;
	t_vec4				org;
	t_vec4				dir;
	t_vec4				tan;
	t_qtype				type;
	float				bounding_radius_sphere;
	float				spec_rs;
	int					spec_ns;
	float				range_z[2];
	int					disruption;
	t_color				color;
	t_xpm				textures[2];
	struct s_quadrics	*next;
}	t_quadrics;

typedef struct s_float_sol
{
	float	sol1;
	float	sol2;
}			t_sols;

int			init_quadrics(t_scene *outscene, char **singlescene);
void		free_quadlist(t_quadrics *quad_list);

t_quadrics	*case_quad_cone(char **cylinder_info);
t_quadrics	*case_quad_cylinder(char **cylinder_info);
t_quadrics	*case_quad_plane(char **single_scene);
t_quadrics	*case_quad_sphere(char **single_scene);
t_quadrics	*case_quadrics(char **single_scene);
void		rotate_quadrics(t_quadrics *Q, t_vec3 axis, float deg);

void		rotate_to_quad_dir(t_quadrics *Q);
float		find_intersection(const t_quadrics *Q, const t_ray *R);
t_vec3		quad_normal_vector(const t_quadrics *Q, t_vec4 p, t_vec4 viewpnt);
t_quadrics	*free_return(t_quadrics	*quadric);
void		fill_quad_matrix(t_mat44 *mat, float coef[5]);

#endif