/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:25:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/01 16:10:16 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_part.h"
#include "scene.h"
#include <stdlib.h>

void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
							unsigned int y, unsigned int color)
{
	char *dst;

	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_mlx_set_image_background(t_mlx *mlx)
{
	unsigned int	x;
	unsigned int	y;

	y = -1;
	while (++y < mlx->height)
	{
		x = -1;
		while (++x < mlx->width)
			ft_mlx_set_pixel_color(mlx->image, x, y, 0xffffff);
	}
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
	ft_mlx_set_image_background(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	return (mlx);
}
void	delete_mlx(t_mlx *mlx)
{
	free_scene(mlx->scene);
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->image);
	free(mlx->mlx);
	free(mlx);
}
