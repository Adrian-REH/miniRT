#include "../main.h"

void control_down(Scene *scene)
{
	scene->cameras->pos.z += 1;
	fmax(fmin(scene->cameras->pos.z, 1.0), -1.0);
	if (!scene->cameras->pos.z)
		scene->cameras->pos.z = 0.1;
	render_scene(scene, N_SAMPLING);
}