/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:13:38 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 15:52:18 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_part.h"
#include "color.h"
#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include <assert.h>
#include "Resoloution.h"

static t_color	intensity_attenuation(t_color color, t_vec3 pos1, t_vec3 pos2)
{
	const int	unit = 128;
	double		dist;
	double		a[3];
	double		attenuation;

	a[0] = 1;
	a[1] = 0;
	a[2] = 0;
	dist = v3_l2norm(v3_sub(pos1, pos2)) / unit;
	attenuation = fmin(1, 1 / (a[0] + a[1] * dist + a[2] * dist * dist));
	return (color_scale(color, attenuation));
}

static void	ft_fill_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	unsigned int	dx;
	unsigned int	dy;

	dx = -1;
	while (++dx < (mlx->edit + 1) && dx + x < WIN_WIDTH)
	{
		dy = -1;
		while (++dy < (mlx->edit + 1) && dy + y < WIN_HEIGHT)
		{
			ft_mlx_set_pixel_color(&(mlx->image), x + dx, y + dy, color);
		}
	}
}

static t_color	single_ray_cast(t_mlx *mlx, t_ray ray)
{
	t_quadrics	*intersect_obj;
	t_vec3		intersect;
	t_color		c;
	double		dist;

	intersect_obj = NULL;
	dist = get_intersect_distance(get_scene()->quads, &intersect_obj, ray);
	if (isinf(dist) == TRUE || isnan(dist) == TRUE)
		return (rgb_color(0, 0, 0));
	else
	{
		intersect = v3_mul(ray.dir, dist - EPSILON);
		intersect = v3_add(intersect, ray.org);
		c = phong_reflection(mlx, intersect_obj, intersect, ray.org);
		return (intensity_attenuation(c, intersect, ray.org));
	}
}

void	*thread_routine(void *ptr)
{
	const t_thread_local_object	*tlo = ptr;
	t_mlx						*mlx;
	double						d;
	unsigned int				pixel[2];
	t_color						color;
	t_ray						ray;

	mlx = tlo->mlx;
	assert(mlx);
	d = (WIN_WIDTH / 2) / tan(get_scene()->cam->hfov / 2);
	pixel[1] = 0;
	while (pixel[1] < WIN_HEIGHT / 2)
	{
		pixel[0] = 0;
		while (pixel[0] < WIN_WIDTH / 2)
		{
			ray.dir = v3_normalize(make_v3((int)(tlo->x + pixel[0] - WIN_WIDTH / 2), \
										(int)(tlo->y + pixel[1] - WIN_HEIGHT / 2), d));
			assert(ray.dir.w == 0);
			ray.org = get_scene()->cam->pos;
			ray.org.w = 1;
			assert(ray.dir.w == 0 && ray.org.w == 1);
			color = single_ray_cast(mlx, ray);
			ft_fill_pixel(mlx, tlo->x + pixel[0], tlo->y + pixel[1], color_to_hex(color));
			pixel[0] += (mlx->edit + 1);
		}
		pixel[1] += (mlx->edit + 1);
	}
	return (NULL);
}
