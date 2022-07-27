/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:47:27 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/26 21:12:33 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_part.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

static double	intersect_plane(t_vec3 ray, t_object_base * obj, unsigned int * pcolor)
{
	double	t;
	double	dist;
	t_vec3	intersection;
	
	if (vec3_dot(ray, obj->org) == 0)
		return (NAN);
	t = vec3_dot(obj->org, obj->normal) / vec3_dot(ray, obj->normal);
	intersection = vec3_scale(ray, t);
	dist = vec3_l2norm(intersection);
	*pcolor = obj->color;
	return (dist);
}

static double	intersect_sphere(t_vec3 ray, t_object_base * obj, unsigned int * pcolor)
{
	double	t[2];
	double	discriminant;
	double	dist;
	t_vec3	intersection;

	discriminant = pow(vec3_l2norm(obj->org), 2) - pow(obj->radius, 2);
	discriminant = discriminant * (pow(vec3_l2norm(ray), 2));
	discriminant = (pow(vec3_dot(ray, obj->org), 2)) - discriminant;
	if (discriminant < 0)
		t[0] = -1;
	else if (discriminant == 0)
		t[0] = vec3_dot(ray, obj->org) / pow(vec3_l2norm(ray), 2);
	else
	{
		t[0] = (vec3_dot(ray, obj->org)) - sqrt(discriminant) / pow(vec3_l2norm(ray), 2);
		t[1] = (vec3_dot(ray, obj->org)) + sqrt(discriminant) / pow(vec3_l2norm(ray), 2);
		if (t[0] < 0)
			t[0] = t[1];
	}
	if (t[0] < 0)
		return (NAN);
	intersection = vec3_scale(ray, t[0]);
	dist = vec3_l2norm(intersection);
	*pcolor = obj->color;
	return (dist);
}

static double	intersect_cylinder(t_vec3 ray, t_object_base * obj, unsigned int * pcolor)
{
	double	t[2];
	double	discriminant;
	double	dist;
	t_vec3	intersection;
	t_vec3	ray_prime;
	t_vec3	org_prime;

	ray_prime = vec3_cross(obj->normal, vec3_cross(ray, obj->normal));
	org_prime = vec3_cross(obj->normal, vec3_cross(obj->org, obj->normal));
	printf("ray : %f, %f, %f\n", ray.x, ray.y, ray.z);
	printf("obj->org : %f, %f, %f\n", obj->org.x, obj->org.y, obj->org.z);
	printf("ray_prime : %f, %f, %f\n", ray_prime.x, ray_prime.y, ray_prime.z);
	printf("org_prime : %f, %f, %f\n", org_prime.x, org_prime.y, org_prime.z);

	discriminant = pow(vec3_l2norm(org_prime), 2) - pow(obj->radius, 2);
	discriminant = discriminant * (pow(vec3_l2norm(ray_prime), 2));
	discriminant = (pow(vec3_dot(ray_prime, org_prime), 2)) - discriminant;
	if (discriminant < 0)
		t[0] = -1;
	else if (discriminant == 0)
		t[0] = vec3_dot(ray_prime, org_prime) / pow(vec3_l2norm(ray_prime), 2);
	else
	{
		t[0] = (vec3_dot(ray_prime, org_prime)) - sqrt(discriminant) / pow(vec3_l2norm(ray_prime), 2);
		t[1] = (vec3_dot(ray_prime, org_prime)) + sqrt(discriminant) / pow(vec3_l2norm(ray_prime), 2);
		if (t[0] < 0)
			t[0] = t[1];
	}
	intersection = vec3_scale(ray_prime, t[0]);

	double height = vec3_dot(vec3_subtract(intersection, obj->org), obj->normal);
	if (0 > height || height > obj->height)
	{
		// 윗 면과 아랫 면 원에 대해서 교점 찾는 과정 필요함.
		return (NAN);
	}
	printf("hieght = %f\n", height);
	dist = vec3_l2norm(intersection);
	*pcolor = obj->color;
	return (dist);
}

double object_intersect(t_vec3 ray, t_object_base * obj, unsigned int * pcolor)
{
	if (ft_strncmp(obj->type, T_PLANE, ft_strlen(T_PLANE) + 1) == 0)
		return (intersect_plane(ray, obj, pcolor));
	else if (ft_strncmp(obj->type, T_SPHERE, ft_strlen(T_SPHERE) + 1) == 0)
		return (intersect_sphere(ray, obj, pcolor));
	else if (ft_strncmp(obj->type, T_CYLINDER, ft_strlen(T_CYLINDER) + 1) == 0)
		return (intersect_cylinder(ray, obj, pcolor));
	else
		return (NAN);
}
