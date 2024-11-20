#include "../main.h"

void init_rfc_render_fun(Scene *scene)
{
	scene->rfc[0] = (int (*)(void *, Ray,  int,  int))render_reflect_plane;//posicion 0
	scene->rfc[1] = (int (*)(void *, Ray,  int,  int))render_reflect_sphere;//posicion 1
	scene->rfc[2] = (int (*)(void *, Ray,  int,  int))render_reflect_triangle;//posicion 2
	scene->rfc[3] = (int (*)(void *, Ray,  int,  int))render_reflect_cylinder;//posicion 3
	scene->rfc[4] = NULL; // NULL 

}
