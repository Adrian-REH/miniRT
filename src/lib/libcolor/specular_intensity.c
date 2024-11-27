/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_intensity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:26:28 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:29 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	specular_intensity(t_vector3 reflection, t_vector3 view_dir, \
	double shininess, double ks)
{
	const double	dot_product = dot(reflection, view_dir);
	const double	intensity = pow(fmax(dot_product, 0.0), shininess) * ks;

	return (intensity);
}
