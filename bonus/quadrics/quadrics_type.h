/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_type.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:24:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 22:30:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRICS_TYPE_H
# define QUADRICS_TYPE_H
# include "color_type.h"
# include "matrix44.h"

typedef enum e_qtype
{
	Q_PLANE = 0,
	Q_QUADRICS
}	t_qtype;

typedef struct s_xpm
{
	void	*img;
	int		img_width;
	int		img_height;
	int		*addr;
	int		bpp;
	int		line;
	int		endian;
}	t_xpm;

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
	t_xpm				bumpmap;
	t_xpm				texture;
	struct s_quadrics	*next;
}	t_quadrics;


#endif