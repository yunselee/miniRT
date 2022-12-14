/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:52:54 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/24 12:42:53 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "vector3.h"

typedef struct s_quadrics	t_quadrics;
typedef struct s_xpm		t_xpm;

typedef struct s_color
{
	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

t_color			rgb_color(unsigned int r, unsigned int g, unsigned int b);

t_color			color_add(t_color c1, t_color c2);

t_color			color_scale(t_color c1, float s);

unsigned int	color_to_hex(t_color color);

t_color			color_disruption(const t_quadrics *Q, \
									t_vec3 point_from_cam, \
									t_color obj_color);

t_color			get_texture_color(const t_quadrics *Q, \
									const t_xpm *texture, \
									t_vec point);

t_color			color_dot(t_color t1, t_color t2, float scale);

#endif
