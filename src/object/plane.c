/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:12 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:29:30 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	plane_solution_point(t_plane plane, t_vector3 point)
{
	const double	d = -(plane.normal.x * plane.point.x + \
		plane.normal.y * plane.point.y + \
		plane.normal.z * plane.point.z);
	const double	result = plane.normal.x * point.x + \
		plane.normal.y * point.y + \
		plane.normal.z * point.z + d;

	if (fabs(result) < EPSILON)
		return (1);
	else
		return (0);
}

int	intersect_plane(const t_ray *ray, const t_plane *plane, double *t)
{
	const double	denom = plane->normal.x * ray->direction.x + \
		plane->normal.y * ray->direction.y + \
		plane->normal.z * ray->direction.z;
	const t_vector3	p0l0 = {
		plane->point.x - ray->origin.x,
		plane->point.y - ray->origin.y,
		plane->point.z - ray->origin.z
	};

	if (fabs(denom) < 1e-6)
		return (0);
	*t = (plane->normal.x * p0l0.x + \
		plane->normal.y * p0l0.y + \
		plane->normal.z * p0l0.z) / denom;
	return (*t > 0);
}

int	find_nearest_plane(t_scene scene, t_ray *ray, t_nearest_ctx *nrst_ctx)
{
	int		i;
	int		j;
	double	min_dist;

	i = -1;
	j = -1;
	min_dist = INT32_MAX;
	while (++i < scene.n_planes)
	{
		if (nrst_ctx->id_o == i && nrst_ctx->type == PLANE)
			continue ;
		if (intersect_plane(ray, &scene.planes[i], &(nrst_ctx->dist)) \
		&& (nrst_ctx->dist < min_dist))
		{
			min_dist = nrst_ctx->dist;
			j = i;
		}
	}
	nrst_ctx->dist = min_dist;
	return (j);
}

void	rot_plane(t_scene *scene, t_vector3 dir, int ang)
{
	t_plane	*plane;

	plane = &(scene->planes[scene->pos_obj->idx]);
	plane->normal = rotate_v3(plane->normal, dir, ang);
	normalize(&plane->normal);
}

void	pos_plane(t_scene *scene, t_vector3 dir)
{
	t_plane	*plane;

	plane = &(scene->planes[scene->pos_obj->idx]);
	plane->point = add_vector3_to_vector3(plane->point, dir);
}
