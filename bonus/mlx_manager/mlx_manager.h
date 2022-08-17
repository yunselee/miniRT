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

# define BACKGROUND (0X222222)

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
typedef struct s_mlx_manager
{
	void				*mlx;
	void				*win;
	t_image				image;
}					t_mlx_manager;

void		init_mlx(char *title_name );

int	destroy_mlx(void* null);

void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color);

void	ft_mlx_set_image_background(t_mlx_manager *mlx);

void	run_mlx(void);

/*===MLX EVENT====*/
void	mlx_renew_image();

//	keydown && move
int		keydown(int keycode);
int		mlx_move_obj(int keycode);
int		mlx_move_light(int keycode);
int		mlx_move_cam(int keycode);
int		mousedown(int button, int x, int y);
int		mlx_mouse_wheel(int keycode);
int		mouseup(int button, int x, int y);
int		mousemove(int x, int y);
void	mlx_replace_light();
t_mlx_manager	*get_mlx(void);

#endif
