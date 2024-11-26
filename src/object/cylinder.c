/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:29:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:29:51 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	cylinder_solution_point(Cylinder cylinder, Vector3 point)
{
	Vector3	cp;
	Vector3	radial;
	double	projection;
	double	radial_distance_squared;
	double	radius_squared;

	radius_squared = pow(cylinder.diameter / 2, 2);
	cp = subtract(point, cylinder.center);
	projection = dot(cp, cylinder.axis);
	if (projection < 0 || projection > cylinder.height)
		return (0);
	radial = subtract(cp, scalev3(cylinder.axis, projection));
	radial_distance_squared = dot(radial, radial);
	if (radial_distance_squared <= radius_squared)
		return (1);
	return (0);
}

Vector3	normal_cylinder(Vector3 hit_point, Cylinder cylinder)
{
	Vector3	normal;
	Vector3	cp;
	double	dot_product;
	Vector3	axis_scaled;

	cp = subtract(hit_point, cylinder.center);
	dot_product = dot(cp, cylinder.axis);
	normal = (Vector3){0, 0, 0};
	if (fabs(dot_product) > (cylinder.height - EPSILON))
	{
		if (dot_product > 0)
			normal = scalev3(cylinder.axis, -1);
		else
			normal = scalev3(cylinder.axis, 1);
	}
	else
	{
		axis_scaled = scalev3(cylinder.axis, dot_product);
		normal = subtract(cp, axis_scaled);
		normalize(&normal);
	}
	return (normal);
}

/*
int	intersect_cylinder(const Ray *ray, const Cylinder *cylinder, double *t)
{
	s_isc_cyl_ctx	ctx;
	double			temp;

	ctx.ro = subtract(cylinder->center, ray->origin);
	ctx.d = ray->direction;
	ctx.ca = cylinder->axis;
	ctx.a = dot(ctx.d, ctx.d) - pow(dot(ctx.d, ctx.ca), 2);
	ctx.b = 2 * (dot(ctx.d, ctx.ro) - dot(ctx.d, ctx.ca) \
	* dot(ctx.ro, ctx.ca));
	ctx.c = dot(ctx.ro, ctx.ro) - pow(dot(ctx.ro, ctx.ca), 2) - \
		pow((cylinder->diameter / 2), 2);
	if (!solve_quadratic((Vector3){ctx.a, ctx.b, ctx.c}, &(ctx.t.x), &(ctx.t.y)))
		return (0);
	if (ctx.t.x > ctx.t.y)
	{
		temp = ctx.t.x;
		ctx.t.x = ctx.t.y;
		ctx.t.y = temp;
	}
	if (ctx.t.x < 0)
	{
		ctx.t.x = ctx.t.y;
		if (ctx.t.x < 0)
			return (0);
	}
	ctx.y.x = dot(ctx.ro, ctx.ca) + ctx.t.x * dot(ctx.d, ctx.ca);
	ctx.y.y = dot(ctx.ro, ctx.ca) + ctx.t.y * dot(ctx.d, ctx.ca);
	ctx.half_h = cylinder->height / 2;
	if (ctx.y.x < -ctx.half_h)
	{
		if (ctx.y.y < -ctx.half_h)
			return (0);
		ctx.th = ctx.t.x + (ctx.t.y - ctx.t.x) *
		 (ctx.y.x + ctx.half_h) / (ctx.y.x - ctx.y.y);
		if (ctx.th <= 0)
			return (0);
		*t = ctx.th;
		return (1);
	}
	else if (ctx.y.x > ctx.half_h)
	{
		if (ctx.y.y > ctx.half_h)
			return (0);
		ctx.th = ctx.t.x + (ctx.t.y - ctx.t.x) * (ctx.y.x - ctx.half_h) / (ctx.y.x - ctx.y.y);
		if (ctx.th <= 0)
			return (0);
		*t = ctx.th;
		return (1);
	}
	*t = ctx.t.x;
	return (1);
}
*/
int	find_nearest_cylinder(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx)
{
	int		i;
	int		j;
	double	min_dist;

	i = -1;
	j = -1;
	min_dist = INT32_MAX;
	while (++i < scene.n_cylinders)
	{
		if (nrst_ctx->id_o == i && nrst_ctx->type == CYLINDER)
			continue ;
		if (intersect_cylinder(ray, &scene.cylinders[i], &(nrst_ctx->dist)) \
		&& (nrst_ctx->dist < min_dist))
		{
			min_dist = nrst_ctx->dist;
			j = i;
		}
	}
	nrst_ctx->dist = min_dist;
	return (j);
}

void	rot_cylinder(Scene *scene, Vector3 dir, int ang)
{
	Cylinder	*cylinder;

	cylinder = &(scene->cylinders[scene->pos_obj->idx]);
	cylinder->axis = rotate_v3(cylinder->axis, dir, ang);
	normalize(&cylinder->axis);
}

void	pos_cylinder(Scene *scene, Vector3 dir)
{
	Cylinder	*cylinder;

	cylinder = &(scene->cylinders[scene->pos_obj->idx]);
	cylinder->center = add_vector3_to_vector3(cylinder->center, dir);
}
