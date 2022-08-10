/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 02:07:33 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/03 14:42:07 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#define BUFFERSIZE 42

static int	read_by_buffer(int fd, char **saving)
{
	char	buf[BUFFERSIZE];
	int		read_size;
	char	*temp;

	while (ft_strchr(*saving, '\n') == NULL)
	{
		read_size = read(fd, buf, BUFFERSIZE - 1);
		if (read_size < 0)
		{
			free(*saving);
			*saving = NULL;
			return (-1);
		}
		buf[read_size] = '\0';
		temp = ft_strjoin(*saving, buf);
		free(*saving);
		*saving = temp;
		if (read_size == 0)
			break ;
	}
	return (read_size);
}

char	*get_next_line(int fd)
{
	static char	*saving;
	char		*temp;
	char		*line;
	int			read_size;

	while (saving == NULL || ft_strchr(saving, '\n') == NULL)
	{
		read_size = read_by_buffer(fd, &saving);
		if (read_size <= 0)
		{
			line = NULL;
			if (read_size == 0 && ft_strlen(saving) > 0)
				line = ft_strdup(saving);
			free(saving);
			saving = NULL;
			return (line);
		}
	}
	temp = ft_strchr(saving, '\n');
	line = ft_substr(saving, 0, temp - saving);
	temp = ft_substr(saving, temp - saving + 1, ft_strlen(temp) - 1);
	free(saving);
	saving = temp;
	return (line);
}
