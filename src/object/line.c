/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:14 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:15 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	line_solution_point(Ray ray, t_vector3 point)
{
	t_vector3	t;

	ft_bzero(&t, sizeof(t_vector3));
	if (!ray.direction.x && point.x != ray.origin.x)
		return (0);
	if (!ray.direction.y && point.y != ray.origin.y)
		return (0);
	if (!ray.direction.z && point.z != ray.origin.z)
		return (0);
	if (ray.direction.x != 0)
		t.y = (point.x - ray.origin.x) / ray.direction.x;
	if (ray.direction.y != 0)
		t.y = (point.y - ray.origin.y) / ray.direction.y;
	if (ray.direction.z != 0)
		t.z = (point.z - ray.origin.z) / ray.direction.z;
	if ((ray.direction.x && ray.direction.y && t.x != t.y) || \
	(ray.direction.x && ray.direction.z && t.x != t.z) || \
	(ray.direction.y && ray.direction.z && t.y != t.z))
		return (0);
	return (t.x);
}
