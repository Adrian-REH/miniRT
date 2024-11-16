#include "../main.h"

int	parser_sphere(Scene *scene, char **data)
{
	scene->spheres = malloc(sizeof(Sphere) * 2);
	scene->spheres[scene->n_spheres].center = (Vector3){0, 0, 3};
	scene->spheres[scene->n_spheres].radius = 1.5;
	scene->spheres[scene->n_spheres].mater_prop.vColor = int_to_color(0xC41414);
	scene->spheres[scene->n_spheres].mater_prop.absorption[R] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r ;
	scene->spheres[scene->n_spheres].mater_prop.absorption[G] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g ;
	scene->spheres[scene->n_spheres].mater_prop.absorption[B] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b ;
	scene->spheres[scene->n_spheres].mater_prop.reflect = 1;
	scene->n_spheres++;
	scene->spheres[scene->n_spheres].center = (Vector3){0, -5, 3};
	scene->spheres[scene->n_spheres].radius = 0.2;
	scene->spheres[scene->n_spheres].mater_prop.vColor = int_to_color(0xFFFFFF);
	scene->spheres[scene->n_spheres].mater_prop.absorption[R] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r ;
	scene->spheres[scene->n_spheres].mater_prop.absorption[G] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g ;
	scene->spheres[scene->n_spheres].mater_prop.absorption[B] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b ;
scene->n_spheres = 0;
}