#include "../main.h"

/**
 * Möller–Trumbore
 */
int intersect_triangle(const Ray *ray, const Triangle *triangle, double *t)
{
    Vector3 edge1, edge2, h, s, q;
	double a, f, u, v;

	edge1 = subtract(triangle->vertex[0], triangle->vertex[1]);
	edge2 = subtract(triangle->vertex[0], triangle->vertex[2]);
	h = cross_v3(ray->direction, edge2);
	a = dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
        return 0;  // El rayo es paralelo al triángulo
    f = 1.0 / a;
    s = subtract(triangle->vertex[0], ray->origin);
    u = f * dot(s, h);
	if (u < 0.0 || u > 1.0)
			return 0;
	q = cross_v3(s, edge1);
	v = f * dot(ray->direction, q);
	if (v < 0.0 || (u + v) > 1.0)
		return 0;
	*t = f * dot(edge2, q);
	if (*t > EPSILON) // Intersección con el triángulo
		return *t;
	return 0;
}

int triangle_solution_point(Triangle triangle, Vector3 hit_pt)
{

	return 0;// no pertenece al triangulo

}

int find_nearest_triangle(Scene scene, Ray *ray, double *t, int id, int type)
{
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_triangles)
	{
		if (id == i && type == TRIANGLE)
			continue ;
		if (intersect_triangle(ray, &scene.triangles[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}