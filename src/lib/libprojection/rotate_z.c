/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_z.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:26:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:23 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	rotate_z(t_vector3 v, double angle)
{
	const double	radians = angle * M_PI / 180.0;
	const double	cos_theta = cos(radians);
	const double	sin_theta = sin(radians);
	t_vector3			result;

	result.x = v.x * cos_theta - v.y * sin_theta;
	result.y = v.x * sin_theta + v.y * cos_theta;
	result.z = v.z;
	return (result);
}
