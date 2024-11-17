#include "../main.h"

int	parser_cylinder(Scene *scene, char **data)
{
	scene->n_cylinders = 0;
	scene->cylinders = malloc(sizeof(Cylinder));
	scene->cylinders->axis = (Vector3){0, -1, 0};
	scene->cylinders->center = (Vector3){0, 5, 1};
	scene->cylinders->height = 4;
	scene->cylinders->diameter = 4;
	scene->cylinders[scene->n_cylinders].mater_prop.reflect = 0;
	scene->cylinders[scene->n_cylinders].mater_prop.vColor = int_to_color(0xFFFFFF);
	scene->cylinders[scene->n_cylinders].mater_prop.absorption[R] = 1 - scene->cylinders[scene->n_cylinders].mater_prop.vColor->r ;
	scene->cylinders[scene->n_cylinders].mater_prop.absorption[G] = 1 - scene->cylinders[scene->n_cylinders].mater_prop.vColor->g ;
	scene->cylinders[scene->n_cylinders].mater_prop.absorption[B] = 1 - scene->cylinders[scene->n_cylinders].mater_prop.vColor->b ;
	scene->n_cylinders++;
}
