/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:31:31 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 10:32:46 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static t_vector3	pxtopy(t_camera cam, t_vector3 v)
{
	t_vector3	dst;

	dst.x = v.x * cam.horizontal.x + v.y * cam.vertical.x + v.z * cam.dir.x;
	dst.y = v.x * cam.horizontal.y + v.y * cam.vertical.y + v.z * cam.dir.y;
	dst.z = v.x * cam.horizontal.z + v.y * cam.vertical.z + v.z * cam.dir.z;
	return (dst);
}

t_ray	*generate_ray(t_vector2 px, int screen_width, \
int screen_height, t_camera camera)
{
	t_ray				*ray;
	t_vector3			point_on_plane;
	const t_vector3	p = {
		.x = ((2.0 * px.x / (double)screen_width) - 1.0) * \
		camera.aspect_ratio * camera.plane_distance,
		.y = (1.0 - 2.0 * px.y / (double)screen_height) * camera.plane_distance,
		.z = 0.5
	};

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->origin = camera.pos;
	point_on_plane = pxtopy(camera, p);
	ray->direction.x = point_on_plane.x;
	ray->direction.y = point_on_plane.y;
	ray->direction.z = point_on_plane.z;
	normalize(&(ray->direction));
	return (ray);
}

t_ray	generate_reflect_ray(t_scene *scene, t_vector3 hit_pt, t_vector3 normal)
{
	t_ray		rayrfc;
	t_vector3	dir_pt;
	t_vector3	rfc;

	dir_pt = norm_subtract(scene->cameras->pos, hit_pt);
	rfc = reflect(dir_pt, normal);
	if (dot(normal, rfc) < 0)
		invnormal(&rfc);
	rayrfc.origin = hit_pt;
	rayrfc.direction = rfc;
	return (rayrfc);
}
