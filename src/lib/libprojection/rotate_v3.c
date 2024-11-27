/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_v3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:26:26 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:27 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/**
 * Rotacion de Rodrigues
 */
t_vector3	rotate_v3(t_vector3 v, t_vector3 axis, double angle)
{
	const double	radians = angle * M_PI / 180.0;
	const double	cos_theta = cos(radians);
	const double	sin_theta = sin(radians);
	const double	dt = dot(v, axis);
	t_vector3			result;

	result.x = v.x * cos_theta + cross_v3(axis, v).x * \
	sin_theta + axis.x * dt * (1 - cos_theta);
	result.y = v.y * cos_theta + cross_v3(axis, v).y * \
	sin_theta + axis.y * dt * (1 - cos_theta);
	result.z = v.z * cos_theta + cross_v3(axis, v).z * \
	sin_theta + axis.z * dt * (1 - cos_theta);
	return (result);
}
