/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_part.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:29:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/17 18:12:03 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_PART_H
# define MLX_PART_H
# include <mlx.h>
# include "scene.h"

# define BACKGROUND (0X222222)

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

typedef struct s_xpm
{
	t_image	img;
	int		img_width;
	int		img_height;
}	t_xpm;

struct s_quadrics;
typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_image				image;
	struct s_quadrics	*selected_quad;
	t_light				*selected_light;
	unsigned int		edit;
	enum e_target		target_scene;
	unsigned int		clicked;
	int					prev_pixel[2];
	int					debug;
}					t_mlx;

int		init_mlx(char *filename );

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
