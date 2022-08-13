/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:58:20 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 17:28:06 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TYPE_H
# define SCENE_TYPE_H
# include "vector3.h"
# include "color_type.h"
# include "quadrics_type.h"
# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

# define EPSILON (0.001)

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}	t_ray;

typedef struct s_light	t_light;
struct s_light
{
	t_vec3	o;
	float	bright;
	t_color	color;
	t_light	*next;
};

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	dir;
	float	hfov;
}	t_cam;

typedef struct s_scene
{
	float		ambient_ratio;
	t_color		ambient_color;
	t_cam		*cam;
	t_mat33		global;
	t_light		*light;
	t_quadrics	*quads;
}	t_scene;


#endif