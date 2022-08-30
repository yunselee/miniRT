/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/30 15:25:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "matrix33.h"
# include "vector3.h"
# include "color.h"

# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

# define EPSILON (0.001)

struct					s_quadrics;
typedef struct s_color	t_color;
typedef struct s_vec	t_vec;
typedef t_vec			t_vec3;

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}	t_ray;

typedef struct s_light	t_light;

typedef struct s_light
{
	t_vec3	o;
	t_color	color;
	float	bright;
	t_light	*next;
}	t_light;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	dir;
	float	hfov;
	double	cam_proportion;
}	t_cam;

typedef struct s_scene
{
	struct s_quadrics	*quads;
	float				ambient_ratio;
	t_color				ambient_color;
	t_cam				*cam;
	t_light				*light;
}	t_scene;

int		scene_init(const char *filename);
void	scene_destroy(void);
int		transform_to_cam_cord(t_scene *scene, t_mat33 transform);
t_scene	*get_scene(void);
float	get_bounding_radius_square(const t_quadrics *Q);

#endif
