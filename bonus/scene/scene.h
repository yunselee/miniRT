/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 18:18:40 by dkim2            ###   ########.fr       */
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

# define EPSILON (1e-5)

struct s_quadrics;
typedef struct s_color t_color;
typedef struct s_vec t_vec;
typedef t_vec	t_vec3;

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}	t_ray;

typedef struct s_light t_light;

typedef struct s_light
{
	t_vec3	o;
	double	bright;
	t_color	color;
	t_light	*next;
} t_light;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	dir;
	double	hfov;
}	t_cam;

typedef struct s_scene
{
	double				ambient_ratio;
	t_color				ambient_color;
	t_cam				*cam;
	t_mat33				global;
	t_light				*light;
	struct s_quadrics	*quads;
}	t_scene;

//t_scene	*create_empty_scene(void);
int		scene_init(const char *filename);
void	scene_destroy(void);
int		transform_to_cam_cord(t_scene *scene, t_mat33 transform);
t_scene	*get_scene(void);

#endif
