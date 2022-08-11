/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:25:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 04:29:23 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#include "scene.h"
#include "mlx_part.h"
#include "print_info.h"
#include "timer.h"

// #include <stdlib.h>
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

int	main(int argc, char **argv)
{
	t_scene	*global_scene;
	t_mat33	transform;

	time_check_start_all();
	if (argc != 2 || argv == NULL)
	{
		printf("Error\n\t: usage : ./miniRT <FILENAME>\n");
		return (1);
	}
	printf("\033[1;33m==============MINI_RT SCENE INFOs==============\033[0m\n");
	global_scene = create_empty_scene();
	if (init_scene(global_scene, argv[1]) == FALSE)
	{
		printf("\033[3;31mError\n\tFail to read file\033[0m\n");
		free_scene(global_scene);
		// system("leaks miniRT");
		return (1);
	}
	print_info_scene(global_scene);
	transform = get_transformation_mat(global_scene->cam->dir);
	transform_to_cam_cord(global_scene, transform);
	print_info_scene(global_scene);
	mlx_start(global_scene, 1920 / 2, 1080 / 2, argv[1]);
	free_scene(global_scene);
	// system("leaks miniRT");
	return (0);
}
