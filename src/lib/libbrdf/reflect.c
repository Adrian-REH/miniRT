/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:11:37 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:04:16 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Vector3	*reflect(Vector3 L, Vector3 N)
{
	Vector3	*reflection;
	double	dot_product;

	dot_product = dot(N, L); // N dot L
	reflection = malloc(sizeof(Vector3));
	*reflection = (Vector3){
		2 * dot_product * N.x - L.x,
		2 * dot_product * N.y - L.y,
		2 * dot_product * N.z - L.z};
	normalize(reflection); // Normalize the reflected vector
	return (reflection);
}
