/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:09 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:10 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	idxfind_min(double *arr, int size)
{
	int		i;
	int		idx;
	double	min;

	if (size <= 0)
		return (0);
	i = 0;
	idx = 0;
	min = arr[i];
	while (++i < size)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			idx = i;
		}
	}
	return (idx);
}

int	find_nearest_obj(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx)
{
	double	distance[10];
	double	idx[10];
	int		type;

	type = -1;
	idx[PLANE] = find_nearest_plane(scene, ray, nrst_ctx);
	distance[PLANE] = nrst_ctx->dist;
	idx[SPHERE] = find_nearest_sphere(scene, ray, nrst_ctx);
	distance[SPHERE] = nrst_ctx->dist;
	idx[CYLINDER] = find_nearest_cylinder(scene, ray, nrst_ctx);
	distance[CYLINDER] = nrst_ctx->dist;
	idx[TRIANGLE] = find_nearest_triangle(scene, ray, nrst_ctx);
	distance[TRIANGLE] = nrst_ctx->dist;
	type = idxfind_min(distance, 4);
	nrst_ctx->id_o = idx[type];
	nrst_ctx->dist = distance[type];
	return (type);
}

int	obj_solution_point(Scene scene, Vector3 point, int type, int id)
{
	if (type == PLANE && !plane_solution_point(scene.planes[id], point))
		return (0);
	if (type == SPHERE && !sphere_solution_point(scene.spheres[id], point))
		return (0);
	if (type == TRIANGLE && \
	!plane_solution_point(scene.triangles[id].p_triangle[0], point))
		return (0);
	if (type == CYLINDER && \
		!cylinder_solution_point(scene.cylinders[id], point))
		return (0);
	return (1);
}
