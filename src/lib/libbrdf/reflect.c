/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:11:37 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 10:32:07 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
/**
 * Reflection vector equation
 */
t_vector3	reflect(t_vector3 L, t_vector3 N)
{
	t_vector3	reflection;
	double		dot_product;

	dot_product = dot(N, L);
	reflection = (t_vector3){
		2 * dot_product * N.x - L.x,
		2 * dot_product * N.y - L.y,
		2 * dot_product * N.z - L.z};
	normalize(&reflection);
	return (reflection);
}
