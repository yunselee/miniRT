/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/26 20:20:53 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "../Libft_vector/matrix33.h"

# ifndef TRUE
# 	define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif
# define T_PLANE ("plane")
# define T_SPHERE ("sphere")
# define T_CYLINDER ("cylinder")

typedef struct s_ray	t_ray;
struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
	t_ray	*next;
};

/*
  plane		-> type : plane		| radius = 0 | height = 0
  sphere	-> type : sphere	| radius = r | height = 0
  cylinder	-> type : cylinder	| radius = r | height = h
*/
typedef struct s_object_base	t_object_base;
struct s_object_base
{
	char			*type;
	unsigned int	color;
	double			radius;
	double			height;
	t_vec3			org;
	t_vec3			normal;
	t_object_base	*next;
};

typedef struct s_light	t_light;
struct s_light
{
	t_vec3	org;
	double	bright;
	t_light	*next;
};

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	dir;
	double	hfov;
}	t_cam;

typedef struct s_scene
{
	double			ambient_ratio;
	unsigned int	ambient_color;
	t_cam			*cam;
	t_mat33			global;
	t_light			*light;
	t_object_base	*obj;
}	t_scene;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}			t_image;

t_scene	*create_empty_scene(void);
int	init_scene(t_scene *scene, char *filename);
void	free_scene(t_scene *pscene);
int	transform_to_cam_cord(t_scene *scene);
// TODO scene 고치지않기

#endif