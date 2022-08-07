/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:25:18 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/07 18:30:27 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_cast.h"

static void	ft_fill_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	unsigned int	s[2];

	s[0] = -1;
	while (++s[0] < (mlx->edit + 1))
	{
		s[1] = -1;
		while (++s[1] < (mlx->edit + 1))
			ft_mlx_set_pixel_color(mlx->image, x + s[0], y + s[1], color);
	}
}

static void	mlx_draw_circle(t_mlx *mlx, int x, int y, int rad)
{
	int	i;
	int	j;

	i = y - rad;
	while (i < y + rad)
	{
		j = x - rad;
		while (j < x + rad)
		{
			if ((x - j) * (x - j) + (y - i) * (y - i) < (rad * rad * 0.8))
				ft_fill_pixel(mlx, j, i, 0xffffff);
			else if ((x - j) * (x - j) + (y - i) * (y - i) < (rad * rad))
				ft_fill_pixel(mlx, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	render_lightsource(t_mlx *mlx, double depth)
{
	t_vec3			cam_to_light;
	unsigned int	x;
	unsigned int	y;
	double			dist;
	t_light			*light;

	light = mlx->scene->light;
	while (light)
	{
		cam_to_light = v3_sub(light->o, mlx->scene->cam->pos);
		dist = v3_l2norm(cam_to_light);
		if (cam_to_light.z > 0 && dist > 0)
		{
			cam_to_light = v3_mul(cam_to_light, dist);
			x = round(cam_to_light.x) + mlx->width / 2;
			y = round(cam_to_light.y) + mlx->height / 2;
			if (x < mlx->width && y < mlx->height)
				mlx_draw_circle(mlx, x, y, \
						fmin(fmax(depth / dist, 5), mlx->height / 4));
		}
		light = light->next;
	}
}
