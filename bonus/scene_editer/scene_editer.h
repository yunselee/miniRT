/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_editer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:18:55 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/24 13:22:05 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_EDITER_H
# define SCENE_EDITER_H

typedef struct s_light	t_light;
enum e_target
{
	E_NONE = 0,
	E_LIGHT,
	E_CAM,
	E_OBJ
};

typedef struct s_scene_editer
{
	struct s_quadrics	*selected_quad;
	t_light				*selected_light;
	unsigned int		edit;
	enum e_target		target_scene;
	unsigned int		clicked;
	int					prev_pixel[2];
	int					debug;
}	t_scene_editer;

t_scene_editer	*get_scene_editer(void);

#endif
