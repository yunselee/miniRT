/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:09:26 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 14:23:54 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include "color.h"
#include "scene.h"
#include "vector3.h"

static t_color ambient_light(t_color obj_color ,t_color ambient_color, double ambient_ratio);

static double diffuse_helper(t_obj_base *objlst, t_light *target_light, t_vec3 normal, t_vec3 intersection);

static t_color diffuse_light(t_scene *scene, t_obj_base *hit_obj, t_vec3 normal, t_vec3 intersection);

static double specular_helper(t_obj_base *objlst, t_light *target_light, t_vec3 mirror_ray, t_vec3 intersection);

static t_color specular_light(t_scene *scene, t_vec3 mirror_ray, t_vec3 intersection);

t_color phong_reflection(t_mlx *mlx, t_obj_base *hit_obj, t_vec3 intersection, t_vec3 view_point)
{
	t_vec3	normal;
	t_vec3	mirror_reflect;
	t_color	radiosity[3];

	// if (mlx->edit != FALSE)
	{
		radiosity[0] = ambient_light(hit_obj->color, mlx->scene->ambient_color, 0.8);
		return (radiosity[0]);
	}
	normal = get_normal_vector(hit_obj, intersection, view_point); 
	intersection = v3_add(intersection, v3_mul(normal, EPSILON));

	mirror_reflect = v3_sub(intersection, view_point);
	mirror_reflect = v3_add(mirror_reflect, v3_mul(normal,-2 * v3_dot(normal, mirror_reflect)));
	mirror_reflect = v3_normalize(mirror_reflect);

	radiosity[0] = ambient_light(hit_obj->color, mlx->scene->ambient_color, mlx->scene->ambient_ratio);
	radiosity[1] = diffuse_light(mlx->scene, hit_obj, normal, intersection);
	radiosity[2] = specular_light(mlx->scene, mirror_reflect, intersection);
	return (color_add(color_add(radiosity[0], radiosity[1]), radiosity[2]));
}

static t_color ambient_light(t_color obj_color ,t_color amb_color, double ra)
{
	t_color	c;
	
	if (ra < 0)
		ra = 0;
	else if (ra > 1)
		ra = 1;
	c.red = round((double)obj_color.red * ra * ((double)amb_color.red / 255));
	c.green = round((double)obj_color.green * ra * ((double)amb_color.green / 255));
	c.blue = round((double)obj_color.blue * ra * ((double)amb_color.blue / 255));
	return (c);
}

static double diffuse_helper(t_obj_base *objlst, t_light *target_light, t_vec3 normal, t_vec3 intersection)
{
	t_obj_base	*target_obj;
	t_vec3			dir_to_light;
	double			dist[2];
	double			diffuse;
	t_ray			ray_to_light;

	dist[0] = INFINITY;
	dir_to_light = (v3_sub(target_light->o, intersection));
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = intersection;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = intersect(ray_to_light, target_obj, NULL);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
			dist[0] = dist[1];
		target_obj = target_obj->next;
	}
	if (isnan(dist[0]) == FALSE && dist[0] < v3_l2norm(dir_to_light))
		return (0);
	diffuse = fmax(0, v3_dot(v3_normalize(dir_to_light), normal)) * target_light->bright;
	return(diffuse);
}

static t_color diffuse_light(t_scene *scene, t_obj_base *hit_obj, t_vec3 normal, t_vec3 intersection)
{
	t_light	*light;
	t_color color;
	double	diffuse;

	color = rgb_color(0, 0, 0);
	light = scene->light;
	while (light != NULL)
	{
		diffuse = diffuse_helper(scene->obj, light, normal, intersection);
		if (diffuse > EPSILON)
		{
			color.red += fmin(255, round(diffuse * ((double)light->color.red / 255) * hit_obj->color.red));
			color.green += fmin(255, round(diffuse * ((double)light->color.green / 255) * hit_obj->color.green));
			color.blue += fmin(255, round(diffuse * ((double)light->color.blue / 255) * hit_obj->color.blue));
		}
		light = light->next;
	}
	return (color);
}

static double specular_helper(t_obj_base *objlst, t_light *target_light, t_vec3 mirror_ray, t_vec3 intersection)
{
	t_obj_base		*target_obj;
	t_vec3			dir_to_light;
	t_ray			ray_to_light;
	double			dist[2];
	double			specular;

	dist[0] = INFINITY;
	dir_to_light = (v3_sub(target_light->o, intersection));
	ray_to_light.dir = v3_normalize(dir_to_light);
	ray_to_light.org = intersection;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = intersect(ray_to_light, target_obj, NULL);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
			dist[0] = dist[1];
		target_obj = target_obj->next;
	}
	if (isnan(dist[0]) == FALSE && dist[0] < v3_l2norm(dir_to_light))
		return (0);
	specular = fmax(0, v3_dot(v3_normalize(dir_to_light), mirror_ray));
	return(specular);
}

static t_color specular_light(t_scene *scene, t_vec3 mirror_ray, t_vec3 intersection)
{
	t_light		*light;
	t_color		color;
	double		specular;

	color = rgb_color(0,0,0);
	light = scene->light;
	while (light)
	{
		specular = specular_helper(scene->obj, light, mirror_ray, intersection);
		if (specular > EPSILON)
		{
			specular = R_S * pow(specular, ALPHA);
			color.red += fmin(255, round(specular * ((double)light->color.red / 255) * light->color.red));
			color.green += fmin(255, round(specular * ((double)light->color.green / 255) * light->color.green));
			color.blue += fmin(255, round(specular * ((double)light->color.blue / 255) * light->color.blue));
		}
		light = light->next;
	}
	return (color);
}
