/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:31:17 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/18 14:34:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "mlx_manager.h"
#include "mlx_keycode.h"
#include "ray_cast.h"
#include "resolution.h"

void	mlx_renew_image(void)
{
	t_mlx_manager	*mlx;

	mlx = get_mlx();
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx->image.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->image.addr = mlx_get_data_addr(mlx->image.img, &(mlx->image.bpp), \
								&(mlx->image.line), &(mlx->image.endian));
	ray_cast();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image.img, 0, 0);
}
