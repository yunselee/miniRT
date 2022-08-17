#include "scene_editer.h"

t_scene_editer *get_scene_editer()
{
	static t_scene_editer scene_editer;

	return &scene_editer;
}