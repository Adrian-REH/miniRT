/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:29:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 20:39:22 by razamora         ###   ########.fr       */
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
