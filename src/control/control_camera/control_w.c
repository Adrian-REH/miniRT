#include "../../main.h"

void	control_w(Scene *scene)
{
	Vector3	axis_of_rotation;

	axis_of_rotation = cross_v3(scene->cameras->dir, scene->cameras->vertical);
	normalize(&axis_of_rotation);  // Normalizar el eje de rotación
	if (scene->pos_obj->rot[scene->pos_obj->type])
		scene->pos_obj->rot[scene->pos_obj->type](scene, axis_of_rotation, 10);
	render_scene(scene, N_SAMPLING);
}
