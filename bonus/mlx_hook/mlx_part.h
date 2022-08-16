/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_part.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:29:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/16 09:22:48 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_PART_H
# define MLX_PART_H
# include <mlx.h>
# include "scene.h"

# define BACKGROUND (0X222222)

int		init_mlx(unsigned int width, \
					unsigned int height, char *filename );

void	destroy_mlx(void);

void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color);

void	ft_mlx_set_image_background(t_mlx *mlx);

void	run_mlx(void);

/*===MLX EVENT====*/
void	mlx_renew_image(t_mlx *mlx);
int		destroy(t_mlx *mlx);

//	keydown && move
int		keydown(int keycode, t_mlx *mlx);
int		mlx_move_obj(t_mlx *mlx, int keycode);
int		mlx_move_light(t_mlx *mlx, int keycode);
int		mlx_move_cam(t_mlx *mlx, int keycode);
int		mousedown(int button, int x, int y, t_mlx *mlx);
int		mlx_mouse_wheel(t_mlx *mlx, int keycode);
int		mouseup(int button, int x, int y, t_mlx *mlx);
int		mousemove(int x, int y, t_mlx *mlx);
void	mlx_switch_light(t_mlx *mlx);
t_mlx	*get_mlx(void);

#endif
