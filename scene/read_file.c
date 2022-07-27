/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:05:07 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/09 19:44:07 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h"
#include "scene.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "in_parsing.h"

static int	parse_scene(t_scene *scene, char *line)
{
	char	**single_scene;
	int		res;
	int		i;

	single_scene = ft_split(line, " \t\v\r\f\n");
	if (!single_scene)
		return (FALSE);
	res = FALSE;
	if (ft_strncmp(single_scene[0], "A", 2) == 0)
		res = case_ambient(scene, single_scene);
	else if (ft_strncmp(single_scene[0], "C", 2) == 0)
		res = case_camera(scene, single_scene);
	else if (ft_strncmp(single_scene[0], "L", 2) == 0)
		res = case_light(scene, single_scene);
	else if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		res = case_sphere(scene, single_scene);
	else if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		res = case_plane(scene, single_scene);
	else if (ft_strncmp(single_scene[0], "cy", 3) == 0)
		res = case_cylinder(scene, single_scene);
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

static int	check_scene(t_scene *scene)
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

int	init_scene(t_scene *scene, char *filename)
{
	int		fd;
	char	*line;

	if (scene == NULL)
		return (FALSE);
	if (ft_strncmp(&filename[ft_strlen(filename) - 3], ".rt", 4))
		return (FALSE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "", 1) && !parse_scene(scene, line))
		{
			free(line);
			terminate_gnl(fd);
			return (FALSE);
		}
		free(line);
	}
	close(fd);
	return (check_scene(scene));
}
