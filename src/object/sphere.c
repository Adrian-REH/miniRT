/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:07 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:09 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static s_sphere_isc_ctx	build_sphere_isc_ctx(const Ray *ray, \
const Sphere *sphere)
{
	s_sphere_isc_ctx	ctx;
	const Vector3		oc = {ray->origin.x - sphere->center.x,
		ray->origin.y - sphere->center.y, \
		ray->origin.z - sphere->center.z};

	ctx = (s_sphere_isc_ctx){
		.a = ray->direction.x * ray->direction.x + \
		ray->direction.y * ray->direction.y + \
		ray->direction.z * ray->direction.z,
		.b = 2.0 * (oc.x * ray->direction.x + \
		oc.y * ray->direction.y + \
		oc.z * ray->direction.z),
		.c = oc.x * oc.x + oc.y * oc.y + oc.z * \
		oc.z - sphere->radius * sphere->radius,
	};
	return (ctx);
}

int	intersect_sphere(const Ray *ray, const Sphere *sphere, double *t)
{
	s_sphere_isc_ctx	ctx;

	ctx = build_sphere_isc_ctx(ray, sphere);
	ctx.discriminant = ctx.b * ctx.b - 4 * ctx.a * ctx.c;
	if (ctx.discriminant >= 0)
	{
		ctx.t1 = (-ctx.b - sqrt(ctx.discriminant)) / (2.0 * ctx.a);
		ctx.t2 = (-ctx.b + sqrt(ctx.discriminant)) / (2.0 * ctx.a);
		if (ctx.t1 > 0)
		{
			*t = ctx.t1;
			return (1);
		}
		if (ctx.t2 > 0)
		{
			*t = ctx.t2;
			return (1);
		}
	}
	return (0);
}

int	sphere_solution_point(Sphere sphere, Vector3 point)
{
	const double	dx = point.x - sphere.center.x;
	const double	dy = point.y - sphere.center.y;
	const double	dz = point.z - sphere.center.z;
	const double	distance_squared = dx * dx + dy * dy + dz * dz;
	const double	radius_squared = sphere.radius * sphere.radius;

	if (fabs(distance_squared - radius_squared) < EPSILON)
		return (1);
	else
		return (0);
}

int	find_nearest_sphere(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx)
{
	int		i;
	int		j;
	double	min_dist;

	i = -1;
	j = -1;
	min_dist = INT32_MAX;
	while (++i < scene.n_spheres)
	{
		if (nrst_ctx->id_o == i && nrst_ctx->type == SPHERE)
			continue ;
		if (intersect_sphere(ray, &scene.spheres[i], &(nrst_ctx->dist)) \
			&& (nrst_ctx->dist < min_dist))
		{
			min_dist = nrst_ctx->dist;
			j = i;
		}
	}
	nrst_ctx->dist = min_dist;
	return (j);
}

void	pos_sphere(Scene *scene, Vector3 dir)
{
	Sphere	*sphere;

	sphere = &(scene->spheres[scene->pos_obj->idx]);
	sphere->center = add_vector3_to_vector3(sphere->center, dir);
}
