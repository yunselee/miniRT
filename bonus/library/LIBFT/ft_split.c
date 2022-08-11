/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:40:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 02:59:30 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	char_in_set(char *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	count_delimeter(char const *s, char *set)
{
	int	i;
	int	is_delimeter;
	int	count;

	i = 0;
	is_delimeter = 1;
	count = 0;
	while (s[i])
	{
		if (char_in_set(set, s[i]))
			is_delimeter = 1;
		else
		{
			if (is_delimeter == 1)
				count++;
			is_delimeter = 0;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char *set)
{
	int			set_idx;
	int			count;
	const char	*start;
	char		**str_set;

	if (s == NULL)
		return (NULL);
	count = count_delimeter(s, set);
	str_set = malloc(sizeof(char *) * (count + 1));
	if (!str_set)
		return (NULL);
	set_idx = 0;
	while (set_idx < count)
	{
		while (char_in_set(set, *s))
			s++;
		if (*s == 0)
			break ;
		start = s;
		while (!char_in_set(set, *s) && *s != 0)
			s++;
		str_set[set_idx++] = ft_strndup(start, s - start);
	}
	str_set[set_idx] = NULL;
	return (str_set);
}
