#include "../main.h"

int	parser_triangle(Scene *scene, char **data)
{
	scene->n_triangles = 0;
	scene->triangle =  malloc(sizeof(Triangle) * 1);
	scene->triangle->vertex[0] = (Vector3){-3, 1, 1};
	scene->triangle->vertex[1] = (Vector3){3, 1, 1};
	scene->triangle->vertex[2] = (Vector3){0, -3, 1};
	scene->triangle->dir[0] = normalize_withpoint(scene->triangle->vertex[0], scene->triangle->vertex[1]);
	scene->triangle->dir[1] = normalize_withpoint(scene->triangle->vertex[2], scene->triangle->vertex[0]);
	scene->triangle->dir[2] = normalize_withpoint(scene->triangle->vertex[2], scene->triangle->vertex[0]);
	scene->triangle->n_vertex = 3;
	scene->triangle->mater_prop.vColor = int_to_color(0xFFFFFF);
	scene->triangle->mater_prop.reflect = 1;
	scene->triangle->mater_prop.absorption[R] = 1 - scene->triangle->mater_prop.vColor->r;
	scene->triangle->mater_prop.absorption[G] = 1 - scene->triangle->mater_prop.vColor->g;
	scene->triangle->mater_prop.absorption[B] = 1 - scene->triangle->mater_prop.vColor->b;
	scene->triangle->p_triangle = malloc(sizeof(Plane));
	scene->triangle->p_triangle->normal = cross_v3(*(scene->triangle->dir[0]), *(scene->triangle->dir[1]));
	scene->triangle->p_triangle->point = scene->triangle->vertex[0];
	//scene->n_triangles++;
}

