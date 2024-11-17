
#include "../main.h"

int	parser_light(Scene *scene, char **data){
	scene->lights = malloc(sizeof(Light));
	scene->lights->color = int_to_color(0xFFFFFF);
	scene->lights->point =  (Vector3){0, 0, 3};
	scene->lights->ratio = 1;
}