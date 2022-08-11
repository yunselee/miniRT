/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:25:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 16:05:49 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx_part.h"
#include "scene.h"
#include "ray_cast.h"
#include "timer.h"

void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_mlx	*create_mlx(t_scene *scene, unsigned int width, \
					unsigned int height, char *filename )
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (NULL == mlx)
		return (NULL);
	mlx->image = malloc(sizeof(t_image));
	if (NULL == mlx->image)
	{
		free(mlx);
		return (NULL);
	}
	mlx->scene = scene;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, width, height, filename);
	mlx->image->img = mlx_new_image(mlx->mlx, width, height);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &(mlx->image->bpp), \
								&(mlx->image->line), &(mlx->image->endian));
	mlx->width = width;
	mlx->height = height;
	// mlx->selected_obj = NULL;
	mlx->selected_light = NULL;
	mlx->edit = 0;
	mlx->target_scene = E_NONE;
	mlx->clicked = 0;
	return (mlx);
}

void	delete_mlx(t_mlx *mlx)
{
	// mlx->selected_obj = NULL;
	mlx->selected_light = NULL;
	free_scene(mlx->scene);
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->image);
	free(mlx);
	system("leaks miniRT");
}

void	mlx_start(t_scene *scene, \
					unsigned int width, \
					unsigned int height, \
					char *name)
{
	t_mlx	*mlx;

	mlx = create_mlx(scene, width, height, name);
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	mlx_hook(mlx->win, 17, 0, destroy, mlx);
	mlx_hook(mlx->win, 2, (1L << 0), keydown, mlx);
	// mlx_hook(mlx->win, 4, (1L << 2), mousedown, mlx);
	// mlx_hook(mlx->win, 5, (1L << 3), mouseup, mlx);
	// mlx_hook(mlx->win, 6, (1L << 6), mousemove, mlx);
	time_check_end_all();
	mlx_loop(mlx->mlx);
}
