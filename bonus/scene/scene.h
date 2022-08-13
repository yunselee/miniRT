/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:22 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 17:10:17 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "../Libft_vector/matrix33.h"
# include "scene_type.h"
# include "color_type.h"
# include "quadrics_type.h"

# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

# define EPSILON (0.001)

//t_scene	*create_empty_scene(void);
int		scene_init(const char *filename);
void	scene_destroy(void);
int		transform_to_cam_cord(t_scene *scene, t_mat33 transform);
t_scene *get_scene();

#endif