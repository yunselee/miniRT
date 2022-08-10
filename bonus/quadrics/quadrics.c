/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:55:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/10 23:25:28 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "quadrics.h"

/*
	pl   : 평면(plane)
	
	sp   : 구(sphere)
		(x^2/r^2) + (y^2/r^2) + (z^2/r^2) = 1
	el   : 타원면(ellipsoid)
		(x^2/a^2) + (y^2/b^2) + (z^2/c^2) = 1
	
	cy   : 원기둥(cylinder)
		(x^2/r^2) + (y^2/r^2) = 1
	elcy : 타원기둥(elliptic Cylinder)
		(x^2/a^2) + (y^2/b^2) = 1
	hycy : 쌍곡기둥(hyperbolic Cylinder)
		(x^2/a^2) - (y^2/b^2) = 1
	pbcy : 포물기둥(Parabolic Cylinder)
		(x^2) + (2ay) = 0
	
	co   : 원뿔(cone)
		(x^2/a^2) + (y^2/a^2) - (z^2/b^2) = 1
	elco : 타원뿔(elliptic Cone)
		(x^2/a^2) + (y^2/b^2) - (z^2/c^2) = 1
	
	elpb : 타원포물면(elliptic paraboloid)
		(x^2/a^2) + (y^2/b^2) - z = 0
	hypb : 쌍곡포물면(Hyperbolic paraboloid)
		(x^2/a^2) - (y^2/b^2) - z = 0

	hb1  : 일엽쌍곡면(Hyperboloid one sheet)
		(x^2/a^2) + (y^2/b^2) - (z^2/c^2) = 1
	hb2  : 이엽쌍곡면(Hyperboloid two sheets)
		(x^2/a^2) + (y^2/b^2) -  (z^2/c^2) = -1
*/
t_quadrics	*init_quadrics(char **single_scene)
{
	t_quadrics	*obj;
	
	if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		obj = case_plane(single_scene);
	else if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		obj = case_sphere(single_scene);
	else if (ft_strncmp(single_scene[0], "cy", 3) == 0)
		obj = case_cylinder(single_scene);
	else
		return (NULL);
	//...
}

t_quadrics	*case_sphere(char **single_scene)
{
	t_quadrics	*newquad;

	if (ft_strsetlen(single_scene) != 6)
		return (NULL);
	
}