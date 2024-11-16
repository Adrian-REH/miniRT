#include "../main.h"

/**
 * Möller–Trumbore
 */
int intersect_triangle(const Ray *ray, const Triangle *triangle, double *t)
{
    Vector3 edge1, edge2, h, s, q;
	double a, f, u, v;

	edge1 = *dir_withpoint(triangle->vertex[0], triangle->vertex[1]);
	edge2 = *dir_withpoint(triangle->vertex[0], triangle->vertex[2]);
	h = cross_v3(ray->direction, edge2);
	a = dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
        return 0;  // El rayo es paralelo al triángulo
    f = 1.0 / a;
    s = *dir_withpoint(triangle->vertex[0], ray->origin);
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
	double	res1;
	double	res2;
	double	res3;
	Vector3 *ap = normalize_withpoint(triangle.vertex[0], hit_pt);
	Vector3 *bp = normalize_withpoint(triangle.vertex[1], hit_pt);
	Vector3 *cp = normalize_withpoint(triangle.vertex[2], hit_pt);

	res1 = dot(*(triangle.dir[0]), *ap);
	res2 = dot(*(triangle.dir[1]), *bp);
	res3 = dot(*(triangle.dir[2]), *cp);
	if (res1 >= 0 && res2 >= 0 && res3 >= 0)
		return 1;
	if (res1 <= 0 && res2 <= 0 && res3 <= 0)
		return 1;
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
		if (intersect_triangle(ray, &scene.triangle[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}