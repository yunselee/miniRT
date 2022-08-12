/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:28:37 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 12:29:07 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_TYPE_H
# define COLOR_TYPE_H

typedef struct s_color
{
	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

#endif