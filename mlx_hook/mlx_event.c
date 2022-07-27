/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:31:17 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/26 12:30:15 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_part.h"
#include <stdlib.h>

int keydown(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		delete_mlx(mlx);
		// system("leaks miniRT");
		exit(0);
	}
	return (0);
}

int	destroy(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	delete_mlx(mlx);
	exit(0);
}
