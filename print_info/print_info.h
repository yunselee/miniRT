/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:30:06 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/07 18:30:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_INFO_H
# define PRINT_INFO_H
# include "scene.h"

void	print_info_light(const t_light *light);
void	print_info_camera(const t_cam *cam);
void	print_info_scene(const t_scene *scene);
void	print_info_object(const t_obj_base *obj);

#endif