/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 05:32:17 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 13:53:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	free_strset(char **strset)
{
	int	i;

	i = 0;
	while (strset[i])
		free(strset[i++]);
	free(strset);
}

static int	fractional_part(char *str, float *frac)
{
	int		p;
	int		i;

	p = 10;
	while (ft_isspace(*str))
		str++;
	*frac = 0.0;
	if (ft_strlen(str) > 7)
		str[7] = '\0';
	i = 0;
	while (ft_isdigit(str[i]))
	{
		*frac += (float)(str[i++] - '0') / p;
		p *= 10;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}

static char	**preprocess(const char *str, int *minus)
{
	char	*temp;
	char	**num;

	temp = ft_strtrim(str, " \t\v\n\r\f");
	if (temp == NULL)
		return (0);
	*minus = 0;
	if ((temp[0] == '-' || temp[0] == '+') && (temp[0] == '-'))
		*minus = 1;
	num = ft_split(temp + *minus, ".");
	free(temp);
	if (num == NULL)
		return (NULL);
	if (ft_isdigit(num[0][0]) == 0)
		return (NULL);
	return (num);
}

int	ft_strtof(const char *str, float *out_res)
{
	char	**num;
	int		minus;
	int		int_part;
	float	frac_part;

	num = preprocess(str, &minus);
	if (num == NULL)
		return (0);
	if (num[0] == NULL || ft_strtoi(num[0], &int_part) == 0)
	{
		free_strset(num);
		return (0);
	}
	int_part = minus * (-int_part) + (1 - minus) * int_part;
	frac_part = 0;
	if (num[1] != NULL && num[2] == NULL && \
		fractional_part(num[1], &frac_part) == 0)
	{
		free_strset(num);
		return (0);
	}
	*out_res = int_part + (1 - minus) * frac_part - minus * frac_part;
	free_strset(num);
	return (1);
}
