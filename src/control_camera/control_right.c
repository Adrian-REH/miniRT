#include "../main.h"
void control_right(Scene *scene)
{
	scene->cameras->pos.x += 1;
	fmax(fmin(scene->cameras->pos.x, 1.0), -1.0);
	if (!scene->cameras->pos.x)
		scene->cameras->pos.x = 0.1;
	render_scene(scene, N_SAMPLING);
}