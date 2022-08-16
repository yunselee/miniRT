/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:31:17 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/13 17:46:32 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "mlx_part.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "Resoloution.h"

void	mlx_renew_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx->image->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &(mlx->image->bpp), \
								&(mlx->image->line), &(mlx->image->endian));
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
}

int	destroy(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	destroy_mlx(mlx);
	exit(0);
}
