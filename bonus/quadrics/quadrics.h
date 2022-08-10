/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/10 23:24:11 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_H
# define QUADRICS_H
# include "color.h"

typedef struct	s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;	
}	t_vec4;

typedef struct	s_mat44
{
	t_vec4	r1;
	t_vec4	r2;
	t_vec4	r3;
	t_vec4	r4;
}	t_mat44;

typedef struct quadrics
{
	t_mat44	coefs;
	t_vec4	org;
	t_vec4	dir;
	t_vec4	tan;
	float	range_x[2];
	float	range_y[2];
	float	range_z[2];
	t_color	color;
	struct quadrics	*next;
}	t_quadrics;

t_quadrics	*init_quadrics(char **singlescene);
t_quadrics	*case_plane(char **single_scene);
t_quadrics	*case_sphere(char **single_scene);
t_quadrics	*case_cylinder(char **single_scene);


#endif