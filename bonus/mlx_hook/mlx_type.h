/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_type.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:24:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 17:28:47 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_TYPE_H
# define MLX_TYPE_H
# include "scene_type.h"
# include "quadrics_type.h"

enum e_target
{
	E_NONE = 0,
	E_LIGHT,
	E_CAM,
	E_OBJ
};

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	unsigned int	width;
	unsigned int	height;
	t_image			*image;
	t_scene			*scene;
	t_quadrics		*selected_quad;
	t_light			*selected_light;
	unsigned int	edit;
	enum e_target	target_scene;
	unsigned int	clicked;
	int				last[2];
}					t_mlx;

#endif