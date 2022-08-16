/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 17:53:27 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_H
# define QUADRICS_H
# include "matrix44.h"
#include "mlx_part.h"
#include "color.h"
typedef enum e_qtype
{
	Q_PLANE = 0,
	Q_QUADRICS
}	t_qtype;

// typedef struct s_xpm
// {
// 	void	*img;
// 	int		img_width;
// 	int		img_height;
// 	int		*addr;
// 	int		bpp;
// 	int		line;
// 	int		endian;
// }	t_xpm;

typedef enum e_texturetype
{
	T_NORMAL = 0,
	T_HEIGHT,
	T_TEXTURE,
}	t_texturetype;

typedef struct s_quadrics
{
	t_qtype				type;
	t_mat44				coefs;
	t_vec4				org;
	t_vec4				dir;
	t_vec4				tan;
	double				spec_rs;
	int					spec_ns;
	double				range_z[2];
	int					disruption;
	t_color				color;
	t_xpm				textures[3];
	struct s_quadrics	*next;
}	t_quadrics;

typedef struct s_double_sol
{
	double	sol1;
	double	sol2;
}			t_sols;

int			init_quadrics(t_scene *outscene, char **singlescene);
void		free_quadlist(t_quadrics *quad_list);

t_quadrics	*case_quad_plane(char **single_scene);
t_quadrics	*case_quad_sphere(char **single_scene);
t_quadrics	*case_quadrics(char **single_scene);
void		rotate_quadrics(t_quadrics *Q, t_vec3 axis, double deg);

void		rotate_to_quad_dir(t_quadrics *Q);
double		find_intersection(const t_quadrics *Q, const t_ray *R);
t_vec3		quad_normal_vector(const t_quadrics *Q, t_vec4 p, t_vec4 viewpnt);

#endif