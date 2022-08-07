/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:26:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/07 19:26:52 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_strtoi(const char *str, int *nbr)
{
	unsigned int	num;
	int				minus;
	int				i;

	num = 0;
	minus = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i++] == '-')
		minus = 1;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i++] - '0');
		if (num > (unsigned int)(INT_MAX + minus))
			return (0);
	}
	if (str[i] != '\0')
		return (0);
	*nbr = (int)num;
	if (minus)
		*nbr *= -1;
	return (1);
}
