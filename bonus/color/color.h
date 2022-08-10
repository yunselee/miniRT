/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:52:54 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 20:00:23 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

t_color			rgb_color(unsigned int r, unsigned int g, unsigned int b);

t_color			color_add(t_color c1, t_color c2);

t_color			color_scale(t_color c1, double s);

unsigned int	color_to_hex(t_color color);

#endif
