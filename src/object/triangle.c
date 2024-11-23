#include "../main.h"

/**
 * Möller–Trumbore
 */
int	intersect_triangle(const Ray *ray, const Triangle *triangle, double *t)
{
	s_triangle_isc_ctx	ctx;

	ctx.edge1 = subtract(triangle->vertex[0], triangle->vertex[1]);
	ctx.edge2 = subtract(triangle->vertex[0], triangle->vertex[2]);
	ctx.h = cross_v3(ray->direction, ctx.edge2);
	ctx.a = dot(ctx.edge1, ctx.h);
	if (ctx.a > -EPSILON && ctx.a < EPSILON)
		return (0);
	ctx.f = 1.0 / ctx.a;
	ctx.s = subtract(triangle->vertex[0], ray->origin);
	ctx.u = ctx.f * dot(ctx.s, ctx.h);
	if (ctx.u < 0.0 || ctx.u > 1.0)
		return (0);
	ctx.q = cross_v3(ctx.s, ctx.edge1);
	ctx.v = ctx.f * dot(ray->direction, ctx.q);
	if (ctx.v < 0.0 || (ctx.u + ctx.v) > 1.0)
		return (0);
	*t = ctx.f * dot(ctx.edge2, ctx.q);
	if (*t > EPSILON)
		return (*t);
	return (0);
}

int	find_nearest_triangle(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx)
{
	int		i;
	int		j;
	double	min_dist;

	i = -1;
	j = -1;
	min_dist = INT32_MAX;
	while (++i < scene.n_triangles)
	{
		if (nrst_ctx->id_o == i && nrst_ctx->type == TRIANGLE)
			continue ;
		if (intersect_triangle(ray, &scene.triangles[i], &nrst_ctx->dist) \
		&& (nrst_ctx->dist < min_dist))
		{
			min_dist = nrst_ctx->dist;
			j = i;
		}
	}
	nrst_ctx->dist = min_dist;
	return (j);
}

void	rot_triangle(Scene *scene, Vector3 dir, int ang)
{
	Triangle	*triangle;

	(void)triangle;
	(void)dir;
	(void)ang;
	triangle = &(scene->triangles[scene->pos_obj->idx]);
}

void	pos_triangle(Scene *scene, Vector3 dir)
{
	Triangle	*triangle;

	triangle = &(scene->triangles[scene->pos_obj->idx]);
	triangle->vertex[0] = add_vector3_to_vector3(dir, triangle->vertex[0]);
	triangle->vertex[1] = add_vector3_to_vector3(dir, triangle->vertex[1]);
	triangle->vertex[2] = add_vector3_to_vector3(dir, triangle->vertex[2]);
}
