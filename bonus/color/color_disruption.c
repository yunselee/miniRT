/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruption.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:55:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 20:22:06 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector3.h"
#include "color.h"
#include "quadrics.h"

static int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static t_color	disrupt_plane_color(const t_quadrics *Q, t_vec3 point, t_color obj_color)
{
	const t_vec3	local_j = v3_normalize(v3_crs(Q->dir, Q->tan));
	int				local_x;
	int				local_y;
	int				disrupt;

	local_x = lroundf(v3_dot(v3_sub(point, Q->org), Q->tan) / 10) % 2;
	local_y = lroundf(v3_dot(v3_sub(point, Q->org), local_j) / 10) % 2;
	disrupt = ft_abs(local_x + local_y) % 2;
	if (disrupt == 0)
		return (obj_color);
	return (rgb_color(255 - obj_color.red, \
						255 - obj_color.green, \
						255 - obj_color.blue));
}

t_color	color_disruption(const t_quadrics *Q, t_vec3 point, t_color obj_color)
{
	t_vec3	point_from_obj;
	float	local_x;
	int		local_y;
	int		disrupt;

	if (Q->disruption == FALSE)
		return (obj_color);
	if (Q->type == Q_PLANE)
		return (disrupt_plane_color(Q, point, obj_color));

	point_from_obj = v3_sub(point, Q->org);
	local_y = lroundf(v3_dot(point_from_obj, Q->dir)) % 2;
	point_from_obj = v3_crs(Q->dir, v3_crs(point_from_obj, Q->dir));
	local_x = v3_dot(point_from_obj, Q->tan) / v3_l2norm(point_from_obj);
	local_x = acosf(local_x) * 180 / M_PI / 15;
	local_x = fabsf(roundf(local_x));
	disrupt = ft_abs((int)(local_x) % 2 + local_y) % 2;
	if (disrupt == 0)
		return (obj_color);
	return (rgb_color(255 - obj_color.red, \
						255 - obj_color.green, \
						255 - obj_color.blue));
}