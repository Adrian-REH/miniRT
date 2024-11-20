
#include "../main.h"

int plane_solution_point(Plane plane, Vector3 point)
{
    // Calcula el término constante D usando el punto del plano
    double D = -(plane.normal.x * plane.point.x + 
                plane.normal.y * plane.point.y + 
                plane.normal.z * plane.point.z);
    // Calcula el valor de la ecuación del plano con el punto dado
    double result = plane.normal.x * point.x + 
                   plane.normal.y * point.y + 
                   plane.normal.z * point.z + D;
    // Verifica si el resultado está dentro del margen de tolerancia
    if (fabs(result) < EPSILON) {
        return 1; // El punto está en el plano
    } else {
        return 0; // El punto no está en el plano
    }
}

int intersect_plane(const Ray *ray, const Plane *plane, double *t)
{
	double denom = plane->normal.x * ray->direction.x +
				   plane->normal.y * ray->direction.y +
				   plane->normal.z * ray->direction.z;

	if (fabs(denom) < 1e-6) {
		return 0;
	}

	Vector3 p0l0 = {
		plane->point.x - ray->origin.x,
		plane->point.y - ray->origin.y,
		plane->point.z - ray->origin.z
	};

	*t = (plane->normal.x * p0l0.x +
		  plane->normal.y * p0l0.y +
		  plane->normal.z * p0l0.z) / denom;

	return (*t > 0); // Si t es positivo, hay intersección en dirección del rayo
}

int find_nearest_plane(Scene scene, Ray *ray, double *t, int id, int type)
{
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_planes)
	{
		if (id == i && type == PLANE)
			continue ;
		if (intersect_plane(ray, &scene.planes[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}
void	rot_plane(Scene *scene, Vector3 dir, int ang)
{
	Plane *plane;
	plane = &(scene->planes[scene->pos_obj->idx]);
	plane->normal = rotate_v3(plane->normal, dir, ang);

    normalize(&plane->normal);
}

void	pos_plane(Scene *scene, Vector3 dir)
{
	Plane *plane;
	plane = &(scene->planes[scene->pos_obj->idx]);
	plane->point = add_vector3_to_vector3(plane->point, dir);
}