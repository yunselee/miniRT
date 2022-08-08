/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:25:18 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/08 15:25:56 by dkim2            ###   ########.fr       */
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
	int		i;
	int		j;
	double	rad_square;

	rad_square = rad * rad;
	i = y - rad - 1;
	while (++i < y + rad)
	{
		j = x - rad - 1;
		while (++j < x + rad)
		{
			if (i < 0 || j < 0 || i >= (int)mlx->height || j >= (int)mlx->width)
			{
				// j++;
				continue ;
			}
			else if ((x - j) * (x - j) + (y - i) * (y - i) < (rad_square * 0.8))
				ft_fill_pixel(mlx, j, i, 0xffffff);
			else if ((x - j) * (x - j) + (y - i) * (y - i) < rad_square)
				ft_fill_pixel(mlx, j, i, 0x000000);
			// j++;
		}
		// i++;
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
		if (cam_to_light.z > EPSILON && dist > (1 - EPSILON))
		{
			cam_to_light = v3_mul(cam_to_light, depth / cam_to_light.z);
			x = round(cam_to_light.x) + mlx->width / 2;
			y = round(cam_to_light.y) + mlx->height / 2;
			if (x < mlx->width && y < mlx->height)
				mlx_draw_circle(mlx, x, y, \
				light->bright * fmin(fmax(depth / dist, 5), mlx->height / 4));
		}
		light = light->next;
	}
}
