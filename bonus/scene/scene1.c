/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 05:05:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/11 22:26:43 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "scene.h"
#include "in_parsing.h"
#include "quadrics.h"

t_scene	*create_empty_scene(void)
{
	return (ft_calloc(1, sizeof(t_scene)));
}

void	free_scene(t_scene *pscene)
{
	free(pscene->cam);
	free_lightlst(pscene->light);
	free_quadlist(pscene->quads);
	free(pscene);
}
