/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:07:19 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:46:00 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H
# include "scene.h"
# include "mlx_part.h"
# include "vector3.h"
# include "color.h"

void	ray_cast(t_mlx *mlx);

t_color	phong_reflection(t_mlx *mlx, \
							t_obj_base *hit_obj, \
							t_vec3 intersection, \
							t_vec3 view_point);

#endif