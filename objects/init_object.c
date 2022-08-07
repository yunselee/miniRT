#include "objects.h"
#include "scene.h"
#include "libft.h"

int	case_plane(t_scene *scene, char **single_scene);
int	case_sphere(t_scene *scene, char **single_scene);
int	case_cylinder(t_scene *scene, char **single_scene);
int case_cone(t_scene *out_scene, char **single_scene);

int init_object(t_scene *out_scene, char **single_scene)
{
	int res;

	res = FALSE;
	
	if (ft_strncmp(single_scene[0], "sp", 3) == 0)
		res = case_sphere(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "pl", 3) == 0)
		res = case_plane(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "cy", 3) == 0)
		res = case_cylinder(out_scene, single_scene);
	else if (ft_strncmp(single_scene[0], "co", 3) == 0)
		res = case_cone(out_scene, single_scene);

	return res;
}
