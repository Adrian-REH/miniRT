#include "../main.h"


int cylinder_solution_point(Cylinder cylinder, Vector3 point)
{
    // Vector desde el centro de la base del cilindro al punto
    Vector3 cp = subtract(point, cylinder.center);
    
    // Proyección de cp sobre el eje del cilindro
    double projection = dot(cp, cylinder.axis);
    
    // Verificar si el punto está entre las bases del cilindro
    if (projection < 0 || projection > cylinder.height)
        return 0;
    
    // Vector perpendicular al eje del cilindro
    Vector3 radial = subtract(cp, scalev3(cylinder.axis, projection));
    
    // Verificar si el punto está dentro del radio del cilindro
    double radial_distance_squared = dot(radial, radial);
    double radius_squared = pow(cylinder.diameter / 2, 2);
    
    if (radial_distance_squared <= radius_squared)
        return 1;
    return 0;
}

Vector3 *normal_cylinder(Vector3 hit_point, Cylinder cylinder)
{
	Vector3 *normal = malloc(sizeof(Vector3));
    Vector3 cp = subtract(hit_point, cylinder.center);

    double dot_product = dot(cp, cylinder.axis);

    if (fabs(dot_product) > (cylinder.height - EPSILON)) {
        // Tapa superior
        if (dot_product > 0) {
            *normal = scalev3(cylinder.axis, -1);
        } 
        // Tapa inferior
        else {
            *normal = scalev3(cylinder.axis, 1);
        }
    } 
    // El punto está en la superficie lateral
    else {
        // Proyección de cp perpendicular al eje
        Vector3 axis_scaled = scalev3(cylinder.axis, dot_product);
        *normal = subtract(cp, axis_scaled);
        normalize(normal);
    }
	return normal;
}
int solve_quadratic(double a, double b, double c, double* t0, double* t1)
{
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return 0;
    
    double q = (b > 0) ? -0.5 * (b + sqrt(discriminant)) : -0.5 * (b - sqrt(discriminant));
    *t0 = q / a;
    *t1 = c / q;
    
    if (*t0 > *t1) {
        double temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
    
    return 1;
}

int intersect_cylinder(const Ray *ray, const Cylinder *cylinder, double *t)
{
    Vector3 ro = subtract(cylinder->center, ray->origin);
    Vector3 d = ray->direction;
    Vector3 ca = cylinder->axis;

    double a = dot(d, d) - pow(dot(d, ca), 2);
    double b = 2 * (dot(d, ro) - dot(d, ca) * dot(ro, ca));
    double c = dot(ro, ro) - pow(dot(ro, ca), 2) - pow((cylinder->diameter / 2), 2);
    double t0, t1;
    if (!solve_quadratic(a, b, c, &t0, &t1))
		return 0;
	if (t0 > t1) {
		double temp = t0;
		t0 = t1;
		t1 = temp;
	}
    double y0 = dot(ro, ca) + t0 * dot(d, ca);
    double y1 = dot(ro, ca) + t1 * dot(d, ca);
    if (y0 < 0)
	{
        if (y1 < 0)
			return 0;
        double th = t0 + (t1 - t0) * (y0) / (y0 - y1);
        if (th <= 0)
			return 0;
        *t = th;
        return 1;
    }
	else if (y0 >= cylinder->height)
	{
        if (y1 >= cylinder->height)
			return 0;
        double th = t0 + (t1 - t0) * (y0 - cylinder->height) / (y0 - y1);
        if (th <= 0)
			return 0;
        *t = th;
        return 1;
    }
    *t = t0;
	return 1;
}

int find_nearest_cylinder(Scene scene, Ray *ray, double *t, int id, int type)
{
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_cylinders)
	{
		if (id == i && type == CYLINDER)
			continue ;
		if (intersect_cylinder(ray, &scene.cylinders[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}