/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:33:16 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 17:33:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"

int	str_to_vec3(char *str, t_vec3 *vec_out)
{
	char	**pos_str;
	int		res;

	pos_str = ft_split(str, ",");
	if (pos_str == NULL)
		return (FALSE);
	res = FALSE;
	if (ft_strsetlen(pos_str) == 3 && \
		ft_strtod(pos_str[0], &(vec_out->x)) && \
		ft_strtod(pos_str[1], &(vec_out->y)) && \
		ft_strtod(pos_str[2], &(vec_out->z)))
		res = TRUE;
	ft_freestrset(pos_str);
	return (res);
}

int	str_to_color(char *str, t_color *color_out)
{
	char	**pos_str;
	int		rgb[3];
	int		res;

	pos_str = ft_split(str, ",");
	if (pos_str == NULL)
		return (FALSE);
	res = FALSE;
	if (ft_strsetlen(pos_str) == 3 && ft_strtoi(pos_str[0], rgb + 0) && \
		ft_strtoi(pos_str[1], rgb + 1) && ft_strtoi(pos_str[2], rgb + 2))
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
	color_out->red = rgb[0];
	color_out->green = rgb[1];
	color_out->blue = rgb[2];
	return (res);
}
