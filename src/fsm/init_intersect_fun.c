#include "../main.h"

void init_intersect_fun(Scene *scene)
{
	scene->isc[0] = (int (*)(const void *, const void *, double *))intersect_plane;//posicion 0
	scene->isc[1] = (int (*)(const void *, const void *, double *))intersect_sphere;//posicion 1
	scene->isc[2] = (int (*)(const void *, const void *, double *))intersect_triangle;//posicion 2
	scene->isc[3] = (int (*)(const void *, const void *, double *))intersect_cylinder;//posicion 3
	scene->isc[4] = NULL; // NULL 
}
