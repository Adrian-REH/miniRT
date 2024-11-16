
#include "../main.h"

/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
int	parser_plane(Scene *scene, char **data)
{
	(void)data;
	scene->planes =  malloc(sizeof(Plane) * 6);
	scene->n_planes = 0;
	scene->planes[scene->n_planes] =  (Plane){{0, 0, 1}, {0, 0, -1}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.reflect = 0;
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{1, 0, 0}, {-10, 0, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xff001d;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xff001d;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xff001d);
	scene->planes[scene->n_planes].mater_prop.reflect = 0;
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{-1, 0, 0}, {10, 0, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0x00ffb5;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0x00ffb5;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0x00ffb5);
	scene->planes[scene->n_planes].mater_prop.reflect = 0;
	scene->planes[scene->n_planes].mater_prop.absorption[R] =1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{0, -1, 0}, {0, 5.5, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.reflect = 0;
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{0, 1, 0}, {0, -5.5, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.reflect = 0;
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{0, 0, 35}, {0, 0, 1}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.reflect = 0;
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	normalize(&scene->planes[0].normal);
	normalize(&scene->planes[1].normal);
	normalize(&scene->planes[2].normal);
	normalize(&scene->planes[3].normal);
	normalize(&scene->planes[4].normal);
	normalize(&scene->planes[5].normal);

}