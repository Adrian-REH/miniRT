/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illuminate_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:54 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 10:29:16 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_color	illuminate_surface(t_color surface_color, t_color light_color, \
	double ints, MaterialProperties prop)
{
	t_color	result;

	result.r = surface_color.r * light_color.r * (1.0 - prop.absorption[R]);
	result.g = surface_color.g * light_color.g * (1.0 - prop.absorption[G]);
	result.b = surface_color.b * light_color.b * (1.0 - prop.absorption[B]);
	result.r = light_color.r + (result.r - light_color.r) * ints * prop.glssns;
	result.g = light_color.g + (result.g - light_color.g) * ints * prop.glssns;
	result.b = light_color.b + (result.b - light_color.b) * ints * prop.glssns;
	result.r = fmin(1.0, fmax(0.0, result.r)) * 255;
	result.g = fmin(1.0, fmax(0.0, result.g)) * 255;
	result.b = fmin(1.0, fmax(0.0, result.b)) * 255;
	result.color = (((int)result.r << 16) | ((int)result.g << 8) | \
		(int)result.b);
	return (result);
}

t_color	darken_surface(t_color *surface_color, double darkness_intensity)
{
	t_color	result;

	result.r = surface_color->r * (1.0 - darkness_intensity);
	result.g = surface_color->g * (1.0 - darkness_intensity);
	result.b = surface_color->b * (1.0 - darkness_intensity);
	result.r = fmin(1.0, fmax(0.0, result.r)) * 255;
	result.g = fmin(1.0, fmax(0.0, result.g)) * 255;
	result.b = fmin(1.0, fmax(0.0, result.b)) * 255;
	result.color = (((int)result.r << 16) | ((int)result.g << 8) | \
		(int)result.b);
	return (result);
}
