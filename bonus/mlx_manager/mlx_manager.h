/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:29:13 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/24 14:01:40 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MANAGER_H
# define MLX_MANAGER_H
# include <mlx.h>

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

struct	s_quadrics;
typedef struct s_mlx_manager
{
	void				*mlx;
	void				*win;
	t_image				image;
}					t_mlx_manager;

void			init_mlx(char *title_name );

int				terminate_mlx(void *null);

void			ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color);

void			ft_mlx_set_image_background(t_mlx_manager *mlx);

void			run_mlx(void);

/*===MLX EVENT====*/
void			mlx_renew_image(void);

//	keydown && move
int				keydown(int keycode);
int				mlx_move_obj(int keycode);
int				mlx_move_light(int keycode);
int				mlx_move_cam(int keycode);
int				mousedown(int button, int x, int y);
int				mlx_mouse_wheel(int keycode);
int				mouseup(int button, int x, int y);
int				mousemove(int x, int y);
void			mlx_replace_light(void);
t_mlx_manager	*get_mlx(void);

// messages
void	edit_mode_info_camera(void);
void	edit_mode_info_object(void);
void	edit_mode_info_light(void);

#endif
