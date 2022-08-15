/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:09:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/15 15:48:45 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "color.h"
#include "quadrics_type.h"

static t_color	int_to_color(int int_color)
{
	t_color	color;

	color.red = (int_color & 0x00ff0000) >> 16;
	color.green = (int_color & 0x0000ff00) >> 8;
	color.blue = int_color & 0x000000ff;
	return (color);
}

static t_color	get_image_pixel_color(const t_image *img, int x, int y)
{
	unsigned int	*color_addr;

	color_addr = (unsigned int *)(img->addr + y * img->line + x * img->bpp / 8);
	return (int_to_color(*color_addr));
}

static t_color	get_plane_texture_color(const t_quadrics *Q, const t_xpm *texture, t_vec3 point)
{
	const t_vec3	binormal = v3_normalize(v3_crs(Q->dir, Q->tan));
	float			local_pnt[2];
	int				pixel[2];

	local_pnt[0] = v3_dot(v3_sub(point, Q->org), Q->tan);
	local_pnt[1] = v3_dot(v3_sub(point, Q->org), binormal);
	pixel[0] = (int)local_pnt[0] % texture->img_width + texture->img_width;
	pixel[1] = (int)local_pnt[1] % texture->img_height + texture->img_height;
	pixel[0] %= texture->img_width;
	pixel[1] %= texture->img_height;
	pixel[1] = texture->img_height - pixel[1] - 1;
	return (get_image_pixel_color(&texture->img, pixel[0], pixel[1]));
}

t_color get_texture_color(const t_quadrics *Q, const t_xpm *texture, t_vec point)
{
	const t_vec3	binormal = v3_crs(Q->dir, Q->tan);
	t_vec3			point_from_obj;
	float			local_pnt[2];
	int				pixel[2];
	
	if (texture->img.img == NULL)
		return (Q->color);
	else if (Q->type == Q_PLANE)
		return (get_plane_texture_color(Q, texture, point));
	point_from_obj = v3_sub(point, Q->org);
	local_pnt[1] = (v3_dot(point_from_obj, Q->dir) - Q->range_z[0]) / (Q->range_z[1] - Q->range_z[0]);
	local_pnt[1] *= texture->img_height;
	pixel[1] = ((int)local_pnt[1] % texture->img_height);
	pixel[1] = texture->img_height - pixel[1] - 1;
	point_from_obj = v3_crs(Q->dir, v3_crs(point_from_obj, Q->dir));
	local_pnt[0] = atan2f(v3_dot(point_from_obj, binormal), v3_dot(point_from_obj, Q->tan)) * 180 / M_PI + 360;
	local_pnt[0] = fmodf(local_pnt[0] + 360, 360);
	local_pnt[0] = local_pnt[0] / 360 * (texture->img_width);
	pixel[0] = ((int)(local_pnt[0])) % (texture->img_width);

	return (get_image_pixel_color(&texture->img, pixel[0], pixel[1]));
}
