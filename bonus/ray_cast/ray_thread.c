/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:13:38 by dkim2             #+#    #+#             */
/*   Updated: 2022/10/28 11:15:22 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_manager.h"
#include "color.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "ray_cast.h"
#include "resolution.h"
#include "scene_editer.h"
#include "debug_msgs.h"

static t_color	intensity_attenuation(t_color color, t_vec3 pos1, t_vec3 pos2)
{
	const int		unit = 128;
	const double	a[3] = {1, 0, 0};
	double			dist;
	double			attenuation;

	dist = v3_l2norm(v3_sub(pos1, pos2)) / unit;
	attenuation = fmin(1, 1 / (a[0] + a[1] * dist + a[2] * dist * dist));
	return (color_scale(color, attenuation));
}

static void	ft_fill_pixel(int x, int y, unsigned int color)
{
	unsigned int	dx;
	unsigned int	dy;

	dx = -1;
	while (++dx < (get_scene_editer()->edit + 1) && dx + x < WIN_WIDTH)
	{
		dy = -1;
		while (++dy < (get_scene_editer()->edit + 1) && dy + y < WIN_HEIGHT)
		{
			ft_mlx_set_pixel_color(&(get_mlx()->image), x + dx, y + dy, color);
		}
	}
}

t_color	single_ray_cast(t_ray ray, int recurse)
{
	t_quadrics	*intersect_obj;
	t_vec3		intersect;
	t_color		c;
	float		dist;

	if (recurse < 0)
		return (rgb_color(0, 0, 0));
	intersect_obj = NULL;
	dist = get_intersect_distance(get_scene()->quads, &intersect_obj, ray);
	debug_single_ray_cast(intersect_obj, &dist, NULL, NULL);
	if (isinf(dist) == TRUE || isnan(dist) == TRUE)
		c = rgb_color(0, 0, 0);
	else
	{
		intersect = v3_mul(ray.dir, dist - EPSILON);
		intersect = v3_mul(ray.dir, dist);
		intersect = v3_add(intersect, ray.org);
		c = phong_reflection(intersect_obj, intersect, ray.org, --recurse);
		c = intensity_attenuation(c, intersect, ray.org);
	}
	debug_single_ray_cast(NULL, NULL, NULL, &c);
	return (c);
}

void	*thread_routine(void *ptr)
{
	const t_thread_local_object	*tlo = ptr;
	const t_cam					*cam = get_scene()->cam;
	unsigned int				p[2];
	t_color						color;
	t_ray						ray;

	p[1] = 0;
	while (p[1] < WIN_HEIGHT / THREAD_PARAM)
	{
		p[0] = 0;
		while (p[0] < WIN_WIDTH / THREAD_PARAM)
		{
			ray.dir = v3_normalize(make_v3(\
			(int)(tlo->x + p[0] - WIN_WIDTH / 2), \
			(int)(tlo->y + p[1] - WIN_HEIGHT / 2), cam->cam_proportion));
			ray.org = cam->pos;
			ray.org.w = 1;
			color = single_ray_cast(ray, RECURSE);
			ft_fill_pixel(tlo->x + p[0], tlo->y + p[1], color_to_hex(color));
			p[0] += (get_scene_editer()->edit + 1);
		}
		p[1] += (get_scene_editer()->edit + 1);
	}
	return (NULL);
}
