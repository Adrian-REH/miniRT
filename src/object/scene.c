#include "../main.h"

int idxfind_min(double *arr, int size)
{
	int i;
	int idx;
	double min;

    if (size <= 0)
        return 0;
	i = 0;
	idx = 0;
	min = arr[i];  // Inicializamos el valor mínimo con el primer elemento
	while (++i < size) {
		if (arr[i] < min) {
			min = arr[i];  // Actualizamos el valor mínimo si encontramos uno menor
			idx = i;
		}
	}
    return idx;  // Retorna el valor mínimo encontrado
}

/**
 * Necesito un mejor algoritmo que recuerde los cuerpos y sepa a cual ir y a cual no
 * para intersectar.
 */
int	find_nearest_obj(Scene scene, Ray *ray, double *t, int *id, int omit)
{
	double distance[10];
	double idx[10];
	int type = -1;
	double d;

	d = *t;
	idx[PLANE] = find_nearest_plane(scene, ray, t, *id, omit);
	distance[PLANE] = *t;
	idx[SPHERE] = find_nearest_sphere(scene, ray, t, *id, omit);
	distance[SPHERE] = *t;
	idx[CYLINDER] = find_nearest_cylinder(scene, ray, t, *id, omit);
	distance[CYLINDER] = *t;
	idx[TRIANGLE] = find_nearest_triangle(scene, ray, t, *id, omit);
	distance[TRIANGLE] = *t;

	type = idxfind_min(distance, 4);
	*id = idx[type];
	*t = distance[type];
	return type;
}

int obj_solution_point(Scene scene, Vector3 point, int type, int id)
{
	if (type == PLANE && !plane_solution_point(scene.planes[id], point))
		return 0;
	if (type == SPHERE && !sphere_solution_point(scene.spheres[id], point))
		return 0;
 	if (type == TRIANGLE && !plane_solution_point(scene.triangles[id].p_triangle[0], point))
		return 0;
 	if (type == CYLINDER && !cylinder_solution_point(scene.cylinders[id], point))
		return 0;
	return 1;
}