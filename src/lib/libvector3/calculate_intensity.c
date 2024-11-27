/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_intensity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:37 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:25:38 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	calculate_intensity(t_vector3 normal, t_vector3 light_dir)
{
	return (fmax(0, -dot(normal, light_dir)));
}
