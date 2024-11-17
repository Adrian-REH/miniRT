/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:06:53 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 21:18:06 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Vector3 substract(Vector3 init, Vector3 end)
{
	Vector3 direction;

	// Calcula el vector de dirección restando los puntos
	direction.x = end.x - init.x;
	direction.y = end.y - init.y;
	direction.z = end.z - init.z;

	return direction;
}