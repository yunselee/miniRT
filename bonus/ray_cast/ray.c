/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 05:03:51 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../Libft_vector/vector3.h"
#include "scene.h"
#include "mlx_part.h"
#include "ray_cast.h"
#include "quadrics.h"
#include "print_info.h"
#include "timer.h"
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 4

float	get_intersect_distance(t_quadrics *objlst, \
								t_quadrics **intersecting_obj_out, \
								t_ray ray)
{
	t_quadrics			*target_obj;
	t_quadrics			*intersect_obj;
	float				dist[2];

	dist[0] = INFINITY;
	intersect_obj = NULL;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = find_intersection(target_obj, &ray);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
		{
			dist[0] = dist[1];
			*intersecting_obj_out = target_obj;
		}
		target_obj = target_obj->next;
	}
	if (*intersecting_obj_out == NULL)
		return (INFINITY);
	if (dist[0] < EPSILON)
		return (NAN);
	return (dist[0]);
}


static void	init_thread_local_object(t_thread_local_object *tlo, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < THREAD_NUM)
	{
		(tlo + i)->mlx = mlx;
		(tlo + i)->x = mlx->width/2 * (i/2);
		(tlo + i)->y = mlx->height/2 * (i%2);
		i++;
	}
}

static void ray_multithread(t_mlx *mlx)
{
	static pthread_t				thread_data[THREAD_NUM];
	static t_thread_local_object	tlo[THREAD_NUM];
	int i;

	init_thread_local_object(tlo, mlx);
	i = 0;
	while(i < THREAD_NUM)
	{
		pthread_create((thread_data + i), NULL, thread_routine, (void *)(tlo + i));
		i++;
	}
	i = 0;
	while(i < THREAD_NUM)
	{
		pthread_join(thread_data[i], NULL);
		i++;
	}
}

void	ray_cast(t_mlx *mlx)
{
	double			d;

	d = ((float)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2);
	time_check_start_sub();

	ray_multithread(mlx);

	if (mlx->edit != 0 && mlx->target_scene != E_NONE)
		render_lightsource(mlx, d);
	time_check_end_sub("ray");
}
