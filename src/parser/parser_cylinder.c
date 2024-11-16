#include "../main.h"

int	parser_cylinder(Scene *scene, char **data)
{
	scene->n_cylinders = 0;
	scene->cylinders = malloc(sizeof(Cylinder));
	scene->cylinders->axis = (Vector3){0, 1, 0};
	scene->cylinders->center = (Vector3){0, 0, 0};
	scene->cylinders->height = 4;
	scene->cylinders->diameter = 2;
}
