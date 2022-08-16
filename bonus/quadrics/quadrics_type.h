/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_type.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:24:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 09:23:28 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_TYPE_H
# define QUADRICS_TYPE_H
# include "color_type.h"
# include "mlx_type.h"
# include "matrix44.h"

typedef enum e_qtype
{
	Q_PLANE = 0,
	Q_QUADRICS
}	t_qtype;

typedef enum e_texturetype
{
	T_NORMAL = 0,
	T_HEIGHT,
	T_TEXTURE,
}	t_texturetype;
typedef struct s_quadrics
{
	t_qtype				type;
	t_mat44				coefs;
	t_vec4				org;
	t_vec4				dir;
	t_vec4				tan;
	t_color				color;
	float				spec_rs;
	int					spec_ns;
	float				range_z[2];
	int					disruption;
	t_xpm				textures[3];
	struct s_quadrics	*next;
}	t_quadrics;

#endif