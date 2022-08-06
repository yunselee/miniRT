/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:25:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 19:57:10 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "scene.h"
#include "mlx_part.h"
#include "print_info.h"
#include "ray_cast.h"

int	main(int argc, char **argv)
{
	t_scene	*global_scene;

	if (argc != 2 || argv == NULL)
	{
		printf("ERR : usage : ./miniRT <FILENAME>\n");
		return (1);
	}
	printf("\033[1;33m==============MINI_RT==============\033[0m\n");
	global_scene = create_empty_scene();
	if (init_scene(global_scene, argv[1]) == FALSE)
	{
		printf("\033[3;31mFail to read file\033[0m\n");
		free_scene(global_scene);
		return (1);
	}
	printf("GLOBAL COORDINATE\n");
	print_info_scene(global_scene);
	transform_to_cam_cord(global_scene);
	printf("CAMERA COORDINATE\n");
	print_info_scene(global_scene);
	mlx_start(global_scene, 800, 600, argv[1]);
	free_scene(global_scene);
}
