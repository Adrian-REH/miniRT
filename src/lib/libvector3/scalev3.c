/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalev3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:14 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:25:16 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Vector3	scalev3(Vector3 v, float scalar)
{
	return ((Vector3){
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	});
}
