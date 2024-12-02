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

t_vector3	scalev3(t_vector3 v, float scalar)
{
	return ((t_vector3){
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	});
}
