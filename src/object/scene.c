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

int	find_nearest_obj(Scene scene, Ray *ray, double *t, int *id)
{
	double distance[10];
	double idx[10];
	int type;

	idx[PLANE] = find_nearest_plane(scene, ray, t);
	distance[0] = *t;
	idx[SPHERE] = find_nearest_sphere(scene, ray, t);
	distance[1] = *t;
	idx[2] = 0;
	//idx[2] = find_nearest_cylinder(scene, ray, &satate[1]);
	//idx[3] = find_nearest_polygon(scene, ray, &satate[1]);
	//idx[4] = 0;
	type = idxfind_min(distance, 2);
	*id = idx[type];
	*t = distance[type];
	return type;
}
