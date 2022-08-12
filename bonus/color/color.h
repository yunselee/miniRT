/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:52:54 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 12:30:21 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "quadrics_type.h"
# include "color_type.h"

t_color			rgb_color(unsigned int r, unsigned int g, unsigned int b);

t_color			color_add(t_color c1, t_color c2);

t_color			color_scale(t_color c1, double s);

unsigned int	color_to_hex(t_color color);

t_color			color_disruption(const t_quadrics	*Q, t_vec3 point_from_cam);

#endif
