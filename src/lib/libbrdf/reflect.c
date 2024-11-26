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
Vector3	reflect(Vector3 L, Vector3 N)
{
	Vector3	reflection;
	double	dot_product;

	dot_product = dot(N, L);
	reflection = (Vector3){
		2 * dot_product * N.x - L.x,
		2 * dot_product * N.y - L.y,
		2 * dot_product * N.z - L.z};
	normalize(&reflection);
	return (reflection);
}
