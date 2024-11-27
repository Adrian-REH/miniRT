/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:26:09 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:09 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	rotate_x(t_vector3 v, double angle)
{
	const double	radians = angle * M_PI / 180.0;
	const double	cos_theta = cos(radians);
	const double	sin_theta = sin(radians);
	t_vector3		result;

	result.x = v.x;
	result.y = v.y * cos_theta - v.z * sin_theta;
	result.z = v.y * sin_theta + v.z * cos_theta;
	return (result);
}
