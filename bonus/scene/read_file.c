/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:05:07 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/08 20:11:42 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h"
#include "scene.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "in_parsing.h"
#include "objects.h"

static int	parse_scene(t_scene *out_scene, char *line)
{
	char	**single_scene;
	int		res;
	int		i;

	single_scene = ft_split(line, " \t\v\r\f\n");
	if (!single_scene)
		return (FALSE);
	res = FALSE;
	res = init_object(out_scene, single_scene);
	if (ft_strncmp(single_scene[0], "A", 2) == 0)
		res = case_ambient(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "C", 2) == 0)
		res = case_camera(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "L", 2) == 0)
		res = case_light(out_scene, single_scene);
	i = 0;
	while (single_scene[i])
		free (single_scene[i++]);
	free(single_scene);
	return (res);
}

static void	terminate_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	check_scene(const t_scene *scene)
{
	if (scene->ambient_ratio == 0)
	{
		printf("no amb\n");
		return (FALSE);
	}
	if (scene->cam == NULL)
	{
		printf("no cam\n");
		return (FALSE);
	}
	if (scene->light == NULL)
	{
		printf("no light\n");
		return (FALSE);
	}
	if (scene->obj == NULL)
	{
		printf("no obj\n");
		return (FALSE);
	}
	return (TRUE);
}

int	init_scene(t_scene *out_scene, const char *filename)
{
	int		fd;
	char	*line;

	if (out_scene == NULL || \
		ft_strncmp(&filename[ft_strlen(filename) - 3], ".rt", 4))
		return (FALSE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "", 1) && !parse_scene(out_scene, line))
		{
			printf("error line : %s\n", line);
			free(line);
			terminate_gnl(fd);
			return (FALSE);
		}
		free(line);
	}
	close(fd);
	return (check_scene(out_scene));
}
