/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_y.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:26:05 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:07 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	rotate_y(t_vector3 v, double angle)
{
	const double	radians = angle * M_PI / 180.0;
	const double	cos_theta = cos(radians);
	const double	sin_theta = sin(radians);
	t_vector3		result;

	result.x = v.x * cos_theta + v.z * sin_theta;
	result.y = v.y;
	result.z = -v.x * sin_theta + v.z * cos_theta;
	return (result);
}
