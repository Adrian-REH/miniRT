/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalizev3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:17 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:25:18 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	normalize(t_vector3 *v)
{
	const double	magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

	if (magnitude > 0)
	{
		v->x /= magnitude;
		v->y /= magnitude;
		v->z /= magnitude;
	}
}

t_vector3	*invnormal(t_vector3 *normal)
{
	normal->x = -normal->x;
	normal->y = -normal->y;
	normal->z = -normal->z;
	return (normal);
}

t_vector3	subtract(t_vector3 init, t_vector3 end)
{
	t_vector3	direction;

	direction.x = end.x - init.x;
	direction.y = end.y - init.y;
	direction.z = end.z - init.z;
	return (direction);
}

t_vector3	norm_subtract(t_vector3 init, t_vector3 end)
{
	t_vector3	direction;

	direction.x = end.x - init.x;
	direction.y = end.y - init.y;
	direction.z = end.z - init.z;
	normalize(&direction);
	return (direction);
}
