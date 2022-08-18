#include "scene_editer.h"

t_scene_editer	*get_scene_editer(void)
{
	static t_scene_editer	scene_editer;

	return (&scene_editer);
}
