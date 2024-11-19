#include "../main.h"

void control_a(Scene *scene)
{
	scene->cameras->dir.x -= 0.1;
	fmax(fmin(scene->cameras->dir.x, 1.0), -1.0);
	if (!scene->cameras->dir.x)
		scene->cameras->dir.x = -0.1;
	render_scene(scene, N_SAMPLING);
}