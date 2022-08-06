/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:31:17 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 20:05:54 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"

static void	mlx_renew_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx->image->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &(mlx->image->bpp), \
								&(mlx->image->line), &(mlx->image->endian));
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
}

int	keydown(int keycode, t_mlx *mlx)
{
	const int	stride = 4;

	printf("keycode : %d\n", keycode);
	if (keycode == ESC)
	{
		delete_mlx(mlx);
		exit(0);
	}
	else if (keycode == RARROW)
		mlx->scene->cam->pos.x += stride;
	else if (keycode == LARROW)
		mlx->scene->cam->pos.x -= stride;
	else if (keycode == UARROW)
		mlx->scene->cam->pos.y -= stride;
	else if (keycode == DARROW)
		mlx->scene->cam->pos.y += stride;
	else if (keycode == KEY_I)
		mlx->scene->cam->pos.z += stride;
	else if (keycode == KEY_O)
		mlx->scene->cam->pos.z -= stride;
	else
		return (0);
	mlx_renew_image(mlx);
	return (0);
}

int	destroy(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	delete_mlx(mlx);
	exit(0);
}

int	mousedown(int button, int x, int y, t_mlx *mlx)
{
	if (!mlx)
		return (0);
	if (button == 1)
		printf("[%u, %u] : \n", x, y);
	return (0);
}
