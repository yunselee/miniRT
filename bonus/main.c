/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:25:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/22 19:05:46 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#include "mlx_manager.h"
#include "print_info.h"
#include "timer.h"
#include "scene.h"
#include <stdlib.h>
#include <scene_editer.h>

static t_mat33	get_transformation_mat(t_vec3 k)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_mat33	mat;

	w = v3_normalize(k);
	u = make_v3(0, 1, 0);
	if (1.0 == w.z)
		v = make_v3(-1, 0, 0);
	else if (-1.0 == w.z)
		v = make_v3(1, 0, 0);
	else
	{
		u = make_v3(w.y, -w.x, 0);
		u = v3_normalize(u);
		v = v3_crs(w, u);
	}
	mat = create_mat33(u, v, w);
	return (mat33_trans(mat));
}

static void	print_size_of(void)
{
	printf("scene size :  %d\n", (int)(sizeof(t_scene)));
	printf("mlx manager size :  %d\n", (int)(sizeof(t_mlx_manager)));
	printf("scene editer  size :  %d\n", (int)(sizeof(t_scene_editer)));
}

int	main(int argc, char **argv)
{
	char	*file_name;
	t_mat33	transform;

	print_size_of();
	time_check_start_all();
	if (argc != 2 || argv == NULL)
	{
		printf("Error\n\t: usage : ./miniRT <FILENAME>\n");
		return (1);
	}
	file_name = argv[1];
	printf("Initiating MLX... : ");
	init_mlx(file_name);
	if (scene_init(file_name) == FALSE)
	{
		printf("\n\033[3;31mError\n\tFail to read file\033[0m\n");
		terminate_mlx(NULL);
		return (1);
	}
	printf("\033[1;33m======MINI_RT SCENE INFOs(global)=====\033[0m\n");
	print_info_scene();
	transform = get_transformation_mat(get_scene()->cam->dir);
	transform_to_cam_cord(get_scene(), transform);
	printf("\033[1;33m======MINI_RT SCENE INFOs(camera)=====\033[0m\n");
	print_info_scene();
	run_mlx();
	scene_destroy();
	return (0);
}
