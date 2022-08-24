/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_editer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:21:25 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/24 13:21:26 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_editer.h"

t_scene_editer	*get_scene_editer(void)
{
	static t_scene_editer	scene_editer;

	return (&scene_editer);
}
