/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:33:16 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 05:42:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"

int	str_to_vec3(char *str, t_vec3 *out_vec)
{
	char	**pos_str;
	int		res;
	float	a[3];

	if (str[ft_strlen(str) - 1] == ',')
		return (FALSE);
	pos_str = ft_split(str, ",");
	if (pos_str == NULL)
		return (FALSE);
	res = 1;
	if ((ft_strsetlen(pos_str) != 3) \
		|| (ft_strtof(pos_str[0], a) == FALSE) \
		|| (ft_strtof(pos_str[1], a + 1) == FALSE) \
		|| (ft_strtof(pos_str[2], a + 2) == FALSE))
	{
		ft_freestrset(pos_str);
		return (FALSE);
	}
	out_vec->x = a[0];
	out_vec->y = a[1];
	out_vec->z = a[2];
	out_vec->w = 0;
	ft_freestrset(pos_str);
	return (res);
}

int	str_to_color(char *str, t_color *out_color)
{
	char	**pos_str;
	int		rgb[3];
	int		res;

	if (str[ft_strlen(str) - 1] == ',')
		return (FALSE);
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
	if ((0 > rgb[0] || 255 < rgb[0]) \
		|| (0 > rgb[1] || 255 < rgb[1]) \
		|| (0 > rgb[2] || 255 < rgb[2]))
		return (FALSE);
	out_color->red = rgb[0];
	out_color->green = rgb[1];
	out_color->blue = rgb[2];
	return (res);
}
