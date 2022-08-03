/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_part.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:29:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 21:48:38 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_PART_H
# define MLX_PART_H
# include <mlx.h>
# include "scene.h"

# define BACKGROUND (0X222222)

enum e_target
{
	E_LIGHT = 0,
	E_CAM,
	E_OBJ
};

typedef struct s_selected
{
	t_obj_base *obj;
}	t_selected;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	unsigned int	width;
	unsigned int	height;
	t_image			*image;
	t_scene			*scene;
}					t_mlx;

t_mlx	*create_mlx(t_scene *scene, unsigned int width, \
					unsigned int height, char *filename );

void	delete_mlx(t_mlx *mlx);

void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color);

void	ft_mlx_set_image_background(t_mlx *mlx);

void	mlx_start(t_scene *scene, unsigned int width, \
					unsigned int height, char *name);

/*===MLX EVENT====*/
int		destroy(t_mlx *mlx);
int		keydown(int keycode, t_mlx *mlx);
int		mousedown(int button, int x, int y, t_mlx *mlx);

#endif
