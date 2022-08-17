/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:25:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 17:34:43 by dkim2            ###   ########.fr       */
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

static void print_size_of()
{
	printf("scene size :  %d\n", (int)sizeof(t_scene));
	printf("mlx manager size :  %d\n", (int)sizeof(t_mlx_manager));
	printf("scene editer  size :  %d\n", (int)sizeof(t_scene_editer));
}

/*
		현재 main, mlx, scene 프로세스 : 
			1. scene_init()에서 .rt file을 읽어와 파싱하고 scene구조체를 구성한다.
			2. 카메라 좌표계를 기준으로 모든 scene을 변환하는 행렬을 get_transform_matrix()에서 구한다.
			3. transform_to_cam_cord()에서 구해진 3x3변환 행렬(회전)을 이용해 scene을 변환한다.
			4. 이렇게 구성된 scene구조체를 가지고 mlx를 구성하고 mlx_loop에 들어간다.
		변경 될 프로세스
			0. t_scene과 t_mlx가 완전히 분리되었다.
			1. 우선 해상도와 .rt filename을 이용해서 빈 mlx를 구성한다.
			2. init_scene을 이용하여 .rt파일을 파싱하고 scene을 구성한다.
			3. transform_to_cam_cord()에서 구해진 3x3변환 행렬(회전)을 이용해 scene을 변환한다.
			4. mlx와 scene이 독립적을 모두 구성되면 mlx_start혹은 run_mlx를 이용해 프로그램을 시작한다.
	*/

int	main(int argc, char **argv)
{
	t_mat33	transform;
	char *file_name;
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
		destroy_mlx(NULL);
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
