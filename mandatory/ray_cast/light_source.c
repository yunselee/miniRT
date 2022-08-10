/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:25:18 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/08 20:18:28 by dkim2            ###   ########.fr       */
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

static void	mlx_draw_circle(t_mlx *mlx, int p[2], t_color color, int rad)
{
	int		i;
	int		j;
	double	r_square;

	r_square = rad * rad;
	i = p[1] - rad - 1;
	while (++i < p[1] + rad)
	{
		j = p[0] - rad - 1;
		while (++j < p[0] + rad)
		{
			if (i < 0 || j < 0 || i >= (int)mlx->height || j >= (int)mlx->width)
				continue ;
			else if (pow(p[0] - j, 2) + pow((p[1] - i), 2) < (r_square * 0.8))
				ft_fill_pixel(mlx, j, i, color_to_hex(color));
			else if (pow(p[0] - j, 2) + pow((p[1] - i), 2) < r_square)
				ft_fill_pixel(mlx, j, i, 0x000000);
		}
	}
}

void	render_lightsource(t_mlx *mlx, double depth)
{
	t_vec3		cam_to_light;
	int			point[2];
	double		dist;
	t_light		*light;

	light = mlx->scene->light;
	while (light)
	{
		cam_to_light = v3_sub(light->o, mlx->scene->cam->pos);
		dist = v3_l2norm(cam_to_light);
		if (cam_to_light.z > EPSILON && dist > (1 - EPSILON))
		{
			cam_to_light = v3_mul(cam_to_light, depth / cam_to_light.z);
			point[0] = round(cam_to_light.x) + mlx->width / 2;
			point[1] = round(cam_to_light.y) + mlx->height / 2;
			if (point[0] < (int)mlx->width && point[1] < (int)mlx->height)
				mlx_draw_circle(mlx, point, light->color, \
				light->bright * fmin(fmax(depth / dist, 5), mlx->height / 4));
		}
		light = light->next;
	}
}
