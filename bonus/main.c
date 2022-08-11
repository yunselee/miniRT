/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:25:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 21:06:38 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "scene.h"
#include "mlx_part.h"
#include "print_info.h"
#include "ray_cast.h"
#include "timer.h"
#include "quadrics.h"


static void print_mat33(const t_mat33 *M)
{
	printf("|% .3f % .3f % .3f|\n", M->r1.x, M->r2.x, M->r3.x);
	printf("|% .3f % .3f % .3f|\n", M->r1.y, M->r2.y, M->r3.y);
	printf("|% .3f % .3f % .3f|\n", M->r1.z, M->r2.z, M->r3.z);
	printf("|% .3f % .3f % .3f|\n", M->r1.w, M->r2.w, M->r3.w);
}

static t_mat33	get_transformation_mat(t_vec3 k)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_mat33	mat;

	w = v3_normalize(k);
	u = make_v3(0, 1, 0);
	if (1.0 == w.z)
		v = make_v3(1, 0, 0);
	else if (-1.0 == w.z)
		v = make_v3(-1, 0, 0);
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
		printf("ERR : usage : ./miniRT <FILENAME>\n");
		return (1);
	}
	printf("\033[1;33m==============MINI_RT SCENE INFOs==============\033[0m\n");
	global_scene = create_empty_scene();
	if (init_scene(global_scene, argv[1]) == FALSE)
	{
		printf("\033[3;31mFail to read file\033[0m\n");
		free_scene(global_scene);
		system("leaks miniRT");
		return (1);
	}
	print_info_scene(global_scene);
	transform = get_transformation_mat(global_scene->cam->dir);
	print_mat33(&transform);
	transform_to_cam_cord(global_scene, transform);
	printf("||=====CAM CORD=====||\n");
	print_info_scene(global_scene);
	{
		t_ray	ray;
		ray.dir = global_scene->cam->dir;
		ray.org = global_scene->cam->pos;
		ray.org.w = 1;
		printf("ray dir: <% .3f % .3f % .3f % .3f>\n", ray.dir.x, ray.dir.y, ray.dir.z, ray.dir.w);
		printf("ray org: <% .3f % .3f % .3f % .3f>\n", ray.org.x, ray.org.y, ray.org.z, ray.org.w);

		float t = find_intersection(global_scene->quads, &ray);
		printf("<%f>\n", t);
		t_vec3	intersect = v3_mul(ray.dir, t);
		printf("hit temp: <% .3f % .3f % .3f % .3f>\n", intersect.x, intersect.y, intersect.z, intersect.w);
		intersect = v3_add(v3_mul(ray.dir, t), ray.org);
		printf("hit : <% .3f % .3f % .3f % .3f>\n", intersect.x, intersect.y, intersect.z, intersect.w);
		intersect.w = 1;
		t_vec3	nor = quad_normal_vector(global_scene->quads, intersect, ray.org);
		printf("normal : <% .3f % .3f % .3f % .3f>\n", nor.x, nor.y, nor.z, nor.w);
		t_color color = diffuse_light(global_scene, global_scene->quads, nor, intersect);
		printf("color : %d %d %d\n", color.red, color.green, color.blue);


		ray.dir = v3_normalize(make_v3(1,0,5));
		printf("ray dir: <% .3f % .3f % .3f % .3f>\n", ray.dir.x, ray.dir.y, ray.dir.z, ray.dir.w);
		printf("ray org: <% .3f % .3f % .3f % .3f>\n", ray.org.x, ray.org.y, ray.org.z, ray.org.w);
		t = find_intersection(global_scene->quads, &ray);
		printf("<%f>\n", t);
		intersect = v3_mul(ray.dir, t);
		printf("hit temp: <% .3f % .3f % .3f % .3f>\n", intersect.x, intersect.y, intersect.z, intersect.w);
		intersect = v3_add(v3_mul(ray.dir, t), ray.org);
		printf("hit : <% .3f % .3f % .3f % .3f>\n", intersect.x, intersect.y, intersect.z, intersect.w);
		intersect.w = 1;
		nor = quad_normal_vector(global_scene->quads, intersect, ray.org);
		printf("normal : <% .3f % .3f % .3f % .3f>\n", nor.x, nor.y, nor.z, nor.w);
		color = diffuse_light(global_scene, global_scene->quads, nor, intersect);
		printf("color : %d %d %d\n", color.red, color.green, color.blue);

		ray.dir = v3_normalize(make_v3(-1,0,5));
		printf("ray dir: <% .3f % .3f % .3f % .3f>\n", ray.dir.x, ray.dir.y, ray.dir.z, ray.dir.w);
		printf("ray org: <% .3f % .3f % .3f % .3f>\n", ray.org.x, ray.org.y, ray.org.z, ray.org.w);
		t = find_intersection(global_scene->quads, &ray);
		printf("<%f>\n", t);
		intersect = v3_mul(ray.dir, t);
		printf("hit temp: <% .3f % .3f % .3f % .3f>\n", intersect.x, intersect.y, intersect.z, intersect.w);
		intersect = v3_add(v3_mul(ray.dir, t), ray.org);
		printf("hit : <% .3f % .3f % .3f % .3f>\n", intersect.x, intersect.y, intersect.z, intersect.w);
		intersect.w = 1;
		nor = quad_normal_vector(global_scene->quads, intersect, ray.org);
		printf("normal : <% .3f % .3f % .3f % .3f>\n", nor.x, nor.y, nor.z, nor.w);
		color = diffuse_light(global_scene, global_scene->quads, nor, intersect);
		printf("color : %d %d %d\n", color.red, color.green, color.blue);
	}
	mlx_start(global_scene, 1920 / 2, 1080 / 2, argv[1]);
	free_scene(global_scene);
	system("leaks miniRT");
	return (0);
}
