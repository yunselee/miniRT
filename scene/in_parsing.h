/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:29:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:29:48 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IN_PARSING_H
# define IN_PARSING_H

#include "scene.h"

// void	ft_addlst_back(t_object_base *objlst, t_object_base *node);
void	free_objectlst(t_object_base *objlst);
int	case_plane(t_scene *scene, char **single_scene);
int	case_sphere(t_scene *scene, char **single_scene);
int	case_cylinder(t_scene *scene, char **single_scene);
t_light	*create_light(t_vec3 pos, double b);
void	free_lightlst(t_light *light);
int	case_light(t_scene *scene, char **single_scene);
int	case_ambient(t_scene *scene, char **single_scene);
int	case_camera(t_scene *scene, char **single_scene);



int	str_to_color(char *str, t_color *color);
int	str_to_vec3(char *str, t_vec3 *v);

#endif