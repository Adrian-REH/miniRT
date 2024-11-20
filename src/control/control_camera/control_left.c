#include "../../main.h"

void control_left(Scene *scene)
{
	Vector3 tmp;
	tmp = scalev3(scene->cameras->horizontal, -1);
	if (scene->pos_obj->pos[scene->pos_obj->type])
		scene->pos_obj->pos[scene->pos_obj->type](scene, tmp);
	render_scene(scene, N_SAMPLING);
}