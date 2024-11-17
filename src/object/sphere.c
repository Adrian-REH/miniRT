#include "../main.h"

int intersect_sphere(const Ray *ray, const Sphere *sphere,  double *t) {
	Vector3 oc = {ray->origin.x - sphere->center.x,
				ray->origin.y - sphere->center.y,
				ray->origin.z - sphere->center.z};

	double a = ray->direction.x * ray->direction.x +
				ray->direction.y * ray->direction.y +
				ray->direction.z * ray->direction.z;

	double b = 2.0 * (oc.x * ray->direction.x +
					  oc.y * ray->direction.y +
					  oc.z * ray->direction.z);
	double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere->radius * sphere->radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant >= 0) {
		double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t1 > 0) {
			*t = t1;
			return 1; // Valid intersection distancia mas corta
		}
	 	if (t2 > 0) {
			*t = t2;
			return 1; // Valid intersection
		}
	}
	return 0; // No valid intersection
}

int sphere_solution_point(Sphere sphere, Vector3 point) {
    // Calculamos la distancia entre el punto y el centro de la esfera
    double dx = point.x - sphere.center.x;
    double dy = point.y - sphere.center.y;
    double dz = point.z - sphere.center.z;

    // Calculamos el cuadrado de la distancia entre el punto y el centro
    double distance_squared = dx * dx + dy * dy + dz * dz;

    // Comparamos la distancia al cuadrado con el radio al cuadrado
    double radius_squared = sphere.radius * sphere.radius;

    // Verificamos si la diferencia es pequeña (con un margen de error)
    if (fabs(distance_squared - radius_squared) < EPSILON) {
        return 1; // El punto está en la superficie de la esfera
    } else {
        return 0; // El punto no está en la superficie de la esfera
    }
}


Vector3 *normal_sphere(Vector3 hit_point, Sphere sphere) {
	Vector3 *normal = malloc(sizeof(Vector3));
	normal->x = hit_point.x - sphere.center.x;
	normal->y = hit_point.y - sphere.center.y;
	normal->z = hit_point.z - sphere.center.z;
	
	// Normaliza la normal
	double length = sqrt(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
	if (length > 0) { // Evita división por cero
		normal->x /= length;
		normal->y /= length;
		normal->z /= length;
	}
	
	return normal;
}

int find_nearest_sphere(Scene scene, Ray *ray, double *t, int id, int type)
{
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_spheres)
	{
		if (id == i && type == SPHERE)
			continue ;
		if (intersect_sphere(ray, &scene.spheres[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}
