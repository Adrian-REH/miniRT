#include "../main.h"

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
    Vector3 ro = subtract(ray->origin, cylinder->center);
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
        double th = t0 + (t1 - t0) * y0 / (y0 - y1);
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
	return 0;
}

int cylinder_solution_point(Triangle triangle, Vector3 hit_pt)
{
return 0;

}

int find_nearest_cylinder(Scene scene, Ray *ray, double *t, int id, int type)
{
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_triangles)
	{
		if (id == i && type == CYLINDER)
			continue ;
		if (intersect_cylinder(ray, &scene.triangle[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}