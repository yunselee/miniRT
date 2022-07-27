/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/27 01:47:45 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mlx_part.h"
#include "../Libft_vector/vector3.h"
#include <stdlib.h>
#include <math.h>

// t_ray	*create_ray(t_vec3 org, t_vec3 dir)
// {
// 	return (NULL);
// }

// void	free_raylst(t_ray **pray)
// {
// 	t_ray	*curr;
// 	t_ray	*next;

// 	curr = *pray;
// 	while (curr)
// 	{
// 		next = curr->next;
// 		free(curr);
// 		curr = next;
// 	}
// 	free(*pray);
// 	*pray = NULL;
// }

#include <stdio.h>
double object_intersect(t_vec3 ray, t_object_base * obj, unsigned int * pcolor);

static unsigned int single_ray_cast(t_mlx *mlx, int x, 
									int y, double depth)
{
	t_vec3			dir;
	t_object_base	*target_obj;
	unsigned int	color[2];
	double			distance[2];
	
	distance[0] = INFINITY;
	color[0] = BACKGROUND;
	target_obj = mlx->scene->obj;
	dir = vec3_normalize(create_vec3(x, y, depth));
	while (target_obj)
	{
		distance[1] = object_intersect(dir, target_obj, &color[1]);
		if ((distance[1] != NAN) && (distance[1] < distance[0]))
		{
			distance[0] = distance[1];
			color[0] = color[1];
		}
		target_obj = target_obj->next;
	}
	return (color[0]);
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

	d = ((double)mlx->width / 2) * atan(mlx->scene->cam->hfov / 2);
	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			color =	single_ray_cast(mlx, x - (int)mlx->width / 2 , y -(int) mlx->height / 2, d);
			ft_mlx_set_pixel_color(mlx->image, x, y, color);
			x++;
		}
		y++;
	}
}