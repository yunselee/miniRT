/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:30:06 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 00:02:40 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_INFO_H
# define PRINT_INFO_H
# include "scene.h"
# include "quadrics.h"

void	print_single_light(const t_light *light);
void	print_info_light(const t_light *light);
void	print_info_camera(const t_cam *cam);
void	print_info_scene();
void	print_single_quadrics(const t_quadrics *Q);
void	print_info_quads(const t_quadrics *Qlst);

#endif