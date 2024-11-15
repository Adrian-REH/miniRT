#include "../main.h"

/**
 * Intersecto la recta con el pplano, si la recta lo intersecta 
 * entonces puedo tenerun punto de interseccionsi tengo 
 * el punto de interseccion entonces compruebo si 
 * ese punto interscta con las rectas, si en el caso de que no de cero
 * verifico su los signos de los resultado de las rectas son menores o mayores a cero
 * en ccaso de que uno falle entonces no esta el punto dentro del plano.
 */
int intersect_triangle(const Ray *ray, const Triangle *triangle, double *t)
{
	double	d;
	double	res1;
	double	res2;
	double	res3;
	Vector3 *u;
	if(intersect_plane(ray, triangle->p_triangle, &d))
	{
		res1 = modcross_product(*(triangle->dir[0]), *u);
		res2 = modcross_product(*(triangle->dir[1]), *u);
		res3 = modcross_product(*(triangle->dir[2]), *u);
		if (res1 > 0 && res2 > 0 && res3 > 0)
			return 1;
		if (res1 < 0 && res2 < 0 && res3 < 0)
			return 1;
	}
	return 0;
}