#include "../main.h"

void init_render_fun(Scene *scene)
{
	scene->render[0] = (int (*)(void *, Vector3,  int))render_plane;//posicion 0
	scene->render[1] = (int (*)(void *, Vector3,  int))render_sphere;//posicion 1
	scene->render[2] = (int (*)(void *, Vector3,  int))render_triangle;//posicion 2
	scene->render[3] = (int (*)(void *, Vector3,  int))render_cylinder;//posicion 3
	scene->render[4] = NULL; // NULL 
}
