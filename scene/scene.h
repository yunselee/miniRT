/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 14:24:11 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "../Libft_vector/matrix33.h"
# include "color.h"
#include "objects.h"

# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

# define EPSILON (0.000001)

typedef struct s_light	t_light;
struct s_light
{
	t_vec3	o;
	double	bright;
	t_color	color;
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
	double		ambient_ratio;
	t_color		ambient_color;
	t_cam		*cam;
	t_mat33		global;
	t_light		*light;
	t_obj_base	*obj;
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
int		init_scene(t_scene *scene, const char *filename);
void	free_scene(t_scene *pscene);
int		transform_to_cam_cord(t_scene *scene, t_mat33 transform);

#endif