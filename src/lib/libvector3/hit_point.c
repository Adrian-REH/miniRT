/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	*hit_point(t_ray ray, double t)
{
	t_vector3	*hit_point;

	hit_point = malloc(sizeof(t_vector3));
	hit_point->x = ray.origin.x + t * ray.direction.x;
	hit_point->y = ray.origin.y + t * ray.direction.y;
	hit_point->z = ray.origin.z + t * ray.direction.z;
	return (hit_point);
}

t_vector3	resolve_hit_point(t_ray ray, double t)
{
	t_vector3	hit_point;

	hit_point.x = ray.origin.x + t * ray.direction.x;
	hit_point.y = ray.origin.y + t * ray.direction.y;
	hit_point.z = ray.origin.z + t * ray.direction.z;
	return (hit_point);
}
