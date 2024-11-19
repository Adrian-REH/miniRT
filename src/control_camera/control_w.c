#include "../main.h"

void control_w(Scene *scene)
{
	scene->cameras->dir.y -= 0.1;
	fmax(fmin(scene->cameras->dir.y, 1.0), -1.0);
	if (!scene->cameras->dir.y)
		scene->cameras->dir.y = -0.1;
	render_scene(scene, N_SAMPLING);
}