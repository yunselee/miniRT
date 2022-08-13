/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:25:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 16:44:00 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx_part.h"
#include "scene.h"
#include "ray_cast.h"
#include "timer.h"


t_mlx *get_mlx()
{
	static t_mlx mlx;

	return &mlx;
}

void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	init_mlx(unsigned int width, \
					unsigned int height, char *filename )
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->image = malloc(sizeof(t_image));
	if (mlx->image == NULL)
		return (FALSE);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, width, height, filename);
	mlx->image->img = mlx_new_image(mlx->mlx, width, height);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &(mlx->image->bpp), \
								&(mlx->image->line), &(mlx->image->endian));
	mlx->width = width;
	mlx->height = height;
	mlx->selected_quad = NULL;
	mlx->selected_light = NULL;
	mlx->edit = 0;
	mlx->target_scene = E_NONE;
	mlx->clicked = 0;
	return (TRUE);
}

void	destroy_mlx()
{
	t_mlx *mlx;

	mlx = get_mlx();
	mlx->selected_quad = NULL;
	mlx->selected_light = NULL;
	scene_destroy();
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->image);
	system("leaks miniRT");
}

void	run_mlx( void )
{
	t_mlx	*mlx;

	mlx = get_mlx();
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	mlx_hook(mlx->win, 17, 0, destroy, mlx);
	mlx_hook(mlx->win, 2, (1L << 0), keydown, mlx);
	mlx_hook(mlx->win, 4, (1L << 2), mousedown, mlx);
	mlx_hook(mlx->win, 5, (1L << 3), mouseup, mlx);
	mlx_hook(mlx->win, 6, (1L << 6), mousemove, mlx);
	time_check_end_all();
	mlx_loop(mlx->mlx);
}
