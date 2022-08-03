/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:34:19 by dkim2            ###   ########.fr       */
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
static t_color intensity_attenuation(t_color color, t_vec3 pos1, t_vec3 pos2)
{
	const int	unit = 100;
	double		dist;
	double		a[3];
	double		attenuation;

	a[0] = 1;
	a[1] = 1;
	a[2] = 0;

	dist = vec3_l2norm(vec3_subtract(pos1, pos2)) / unit;
	attenuation = fmin(1, 1 / (a[0] + a[1] * dist + a[2] * dist * dist));
	return (color_scale(color, attenuation));
}

unsigned int	single_ray_cast(t_mlx *mlx, t_vec3 ray, t_vec3 offset)
{
	t_vec3			dir;
	t_object_base	*target_obj;
	t_object_base	*intersect_obj;
	unsigned int	color[2];
	double			distance[2];

	distance[0] = INFINITY;
	color[0] = BACKGROUND;
	target_obj = mlx->scene->obj;
	dir = vec3_normalize(ray);
	intersect_obj = NULL;
	while (target_obj)
	{
		distance[1] = object_intersect(dir, target_obj, &color[1], offset);
		if ((distance[1] != NAN) && (distance[1] < distance[0]))
		{
			distance[0] = distance[1];
			color[0] = color[1];
			intersect_obj = target_obj;
		}
		target_obj = target_obj->next;
	}
	if (intersect_obj == NULL)
		return (BACKGROUND);
	else
	{
		t_vec3	intersect;
		t_color c;
		intersect = vec3_scale(ray, distance[0]);
		c = phong_reflection(mlx, intersect_obj, intersect, mlx->scene->cam->pos);
		return (color_to_hex(intensity_attenuation(c, intersect, mlx->scene->cam->pos)));
	}
}

/*
	mlx->scene->camera->hfov에 저장된 라디안 값을 이용해, 공간 상의 가상의 스크린까지의 거리를 구해야 한다.(카메라로 부터 스크린 까지 거리)
	tan(hfov / 2) = (mlx->width / 2) / depth. depth = (mlx->width / 2) / tan(hfov / 2) = mlx->width / 2 * atan(hfov / 2);
*/
void	ray_cast(t_mlx *mlx)
{
	unsigned int	x;
	unsigned int	y;
	double			d;
	unsigned int	color;
	t_vec3			ray;
	clock_t 		start, end;

	d = ((double)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2);
	y = 0;
	start = clock();
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			ray = create_vec3((int)(x - mlx->width / 2), (int)(y - mlx->height / 2), d);
			color = single_ray_cast(mlx, vec3_normalize(ray), mlx->scene->cam->pos);
			ft_mlx_set_pixel_color(mlx->image, x, y, color);
			x++;
		}
		y++;
	}
	end = clock();
	printf("time : %lu(ms)\n", ((end - start) / 1000));
}
