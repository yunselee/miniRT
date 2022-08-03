/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 21:00:13 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "../Libft_vector/vector3.h"
#include "scene.h"
#include "mlx_part.h"
#include "ray_cast.h"
#include <stdio.h>
#include <time.h>

static t_color	intensity_attenuation(t_color color, t_vec3 pos1, t_vec3 pos2)
{
	const int	unit = 100;
	double		dist;
	double		a[3];
	double		attenuation;

	a[0] = 1;
	a[1] = 1;
	a[2] = 0;
	dist = v3_l2norm(v3_sub(pos1, pos2)) / unit;
	attenuation = fmin(1, 1 / (a[0] + a[1] * dist + a[2] * dist * dist));
	return (color_scale(color, attenuation));
}

static double	get_intersect_distance(t_obj_base *objlst, \
								t_obj_base **intersecting_obj_out, \
								t_vec3 ray, \
								t_vec3 offset)
{
	t_vec3			dir;
	t_obj_base		*target_obj;
	unsigned int	color[2];
	double			dist[2];

	dist[0] = INFINITY;
	color[0] = BACKGROUND;
	target_obj = objlst;
	dir = v3_normalize(ray);
	*intersecting_obj_out = NULL;
	while (target_obj)
	{
		dist[1] = object_intersect(dir, target_obj, &color[1], offset);
		if ((dist[1] != NAN) && (dist[1] < dist[0]))
		{
			dist[0] = dist[1];
			color[0] = color[1];
			*intersecting_obj_out = target_obj;
		}
		target_obj = target_obj->next;
	}
	if (*intersecting_obj_out == NULL)
		return (INFINITY);
	return (dist[0]);
}

static t_color	single_ray_cast(t_mlx *mlx, t_vec3 ray, t_vec3 offset)
{
	t_obj_base	*intersect_obj;
	t_vec3		intersect;
	t_color		c;
	double		dist;

	intersect_obj = NULL;
	dist = get_intersect_distance(mlx->scene->obj, &intersect_obj, ray, offset);
	if (dist == INFINITY)
		return (rgb_color(0, 0, 0));
	else
	{
		intersect = v3_mul(ray, dist);
		intersect = v3_add(intersect, offset);
		c = phong_reflection(mlx, intersect_obj, intersect, offset);
		return (intensity_attenuation(c, intersect, offset));
	}
}

void	ray_cast(t_mlx *mlx)
{
	unsigned int	x;
	unsigned int	y;
	double			d;
	t_color			color;
	t_vec3			ray;

	d = ((double)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2);
	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			ray = make_v3((int)(x - mlx->width / 2), \
						(int)(y - mlx->height / 2), d);
			color = single_ray_cast(mlx, v3_normalize(ray), \
									mlx->scene->cam->pos);
			ft_mlx_set_pixel_color(mlx->image, x, y, color_to_hex(color));
			x++;
		}
		y++;
	}
}
