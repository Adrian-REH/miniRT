/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_attenuation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:45 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:29:03 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	calculate_attenuation(double distance, double k_c, \
	double k_l, double k_q)
{
	return (1.0 / (k_c + k_l * distance + k_q * distance * distance));
}
