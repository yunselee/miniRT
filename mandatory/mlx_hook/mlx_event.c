/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:31:17 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/23 19:59:23 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"

void	mlx_renew_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx->image->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &(mlx->image->bpp), \
								&(mlx->image->line), &(mlx->image->endian));
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
}

int	destroy(t_mlx *mlx)
{
	printf("Terminate MLX\n");
	if (!mlx)
		return (0);
	delete_mlx(mlx);
	system("leaks miniRT");
	exit(0);
}
