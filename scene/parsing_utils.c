/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:33:16 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/26 14:59:37 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h"
#include "scene.h"

int	str_to_vec3(char *str, t_vec3 *v)
{
	char	**pos_str;
	int		res;

	pos_str = ft_split(str, ",");
	if (pos_str == NULL)
		return (FALSE);
	res = FALSE;
	if (ft_strsetlen(pos_str) == 3 && \
		ft_strtod(pos_str[0], &(v->x)) && \
		ft_strtod(pos_str[1], &(v->y)) && \
		ft_strtod(pos_str[2], &(v->z)))
		res = TRUE;
	ft_freestrset(pos_str);
	return (res);
}

int	str_to_color(char *str, unsigned int *color)
{
	char	**pos_str;
	int		rgb[3];
	int		res;

	pos_str = ft_split(str, ",");
	if (pos_str == NULL)
		return (FALSE);
	res = FALSE;
	if (ft_strsetlen(pos_str) == 3 && \
		ft_strtoi(pos_str[0], rgb + 0) && \
		ft_strtoi(pos_str[1], rgb + 1) && \
		ft_strtoi(pos_str[2], rgb + 2))
		res = TRUE;
	ft_freestrset(pos_str);
	if (res == FALSE)
		return (FALSE);
	if (0 > rgb[0] || 255 < rgb[0])
		return (FALSE);
	if (0 > rgb[1] || 255 < rgb[1])
		return (FALSE);
	if (0 > rgb[2] || 255 < rgb[2])
		return (FALSE);
	*color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (res);
}
