
#include <math.h>
#include <stdlib.h>
#include "ray_cast.h"
#include "scene.h"
#include <assert.h>
#include <stdio.h>
#include "debug_msgs.h"

static t_color	object_specular(t_ray reflect_ray, \
								int recurse, \
								float specular_rs)
{
	t_color	color;

	color = single_ray_cast(reflect_ray, recurse);
	color = color_scale(color, specular_rs * specular_rs);
	return (color);
}

static void zero_return(float *outDiffuse,float *outSpecular)
{
	*outSpecular = 0;
	*outDiffuse = 0;
}

static void helper(
	t_quadrics *hit_obj, \
	const t_light *target_light, \
	t_ray reflect_ray,
	t_vec3 normal ,
	float out[2])
{
	const t_vec3	p_to_l = v3_sub(target_light->o, reflect_ray.org);
	const float 	len = v3_l2norm(p_to_l);
	const t_ray		ray_to_light = {reflect_ray.org, v4_mul(p_to_l, 1/len)};
	float			distance;

	debug_light(target_light);
	out[0] = v3_dot(ray_to_light.dir, normal);
	out[1] = v3_dot(ray_to_light.dir, reflect_ray.dir);
	if (out[0] <= 0 && out[1] <= 0)
		zero_return(&out[0], &out[1]);
	distance = get_intersect_distance(get_scene()->quads, NULL, ray_to_light);
	debug_diffuse(&distance, &len, NULL);
	if (isnan(distance) == FALSE && distance < len + EPSILON)
		zero_return(&out[0], &out[1]);
	out[0] *= target_light->bright;
	out[1] = (hit_obj->spec_rs) * pow(out[1], hit_obj->spec_ns);
	debug_diffuse(NULL, NULL, &out[0]);
	if (out[0] < EPSILON)
		out[0] = 0;
	if (out[1] < EPSILON)
		out[1] = 0;
}

t_color color_dot(t_color t1, t_color t2, float scale)
{
	t_color out;
	out.red = ((float)t1.red / 255 * t2.red);
	out.green = ((float)t1.green / 255 * t2.green);
	out.blue = ((float)t1.blue / 255 * t2.blue);
	out = color_scale(out, scale);
	return out;
}

t_color diffuse_specular(
					t_quadrics *hit_obj, \
					t_vec3 normal, \
					t_vec3 hit_point,
					t_vec3 mirror_ray,
					int recurse
					)
{
	const t_color	oclr = color_disruption(hit_obj, hit_point, \
				get_texture_color(hit_obj, &(hit_obj->textures[T_TEXTURE]), hit_point));
	const t_light	*light = get_scene()->light;;
	t_color			c;
	float			diffuse[2];
	const t_ray		reflect_ray = {hit_point , mirror_ray};

	hit_point = v3_add(hit_point, v3_mul(normal, EPSILON));
	c = rgb_color(0, 0, 0);
	debug_diffuse(NULL, NULL, NULL);
	while (light != NULL)
	{
		debug_light(light);
		helper(hit_obj, light, reflect_ray, normal, diffuse);
		if (diffuse[0] > 0)
			c = color_add(c, color_dot(light->color, oclr, \
					diffuse[0] * (1 - hit_obj->spec_rs)));
		if(diffuse[1] > 0)
			c = color_add(c, color_scale(light->color, diffuse[1] * light->bright));
		c = color_add(c, object_specular(reflect_ray, recurse, hit_obj->spec_rs));
		light = light->next;
	}
	return (c);
}

