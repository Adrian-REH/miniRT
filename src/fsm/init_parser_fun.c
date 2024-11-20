#include "../main.h"

void init_parser_fun(Scene *scene)
{
	scene->parser[0] = (int (*)(void *, void *))parser_resolution;//posicion 0
	scene->parser[1] = (int (*)(void *, void *))parser_ambient;//posicion 1
	scene->parser[2] = (int (*)(void *, void *))parser_camera;//posicion 2
	scene->parser[3] = (int (*)(void *, void *))parser_light;//posicion 3
	scene->parser[4] = (int (*)(void *, void *))parser_plane;//posicion 4
	scene->parser[5] = (int (*)(void *, void *))parser_sphere;//posicion 5
	scene->parser[6] = (int (*)(void *, void *))parser_square;//posicion 6
	scene->parser[7] = (int (*)(void *, void *))parser_cylinder;//posicion 7
	scene->parser[8] = (int (*)(void *, void *))parser_triangle;//posicion 8
	scene->parser[9] = NULL; // NULL 
}
