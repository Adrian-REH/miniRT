/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addv3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:26:21 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:26:22 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	add_vector3_to_vector3(t_vector3 init, t_vector3 end)
{
	return ((t_vector3){
		init.x + end.x,
		init.y + end.y,
		init.z + end.z
	});
}

t_vector3	add_scalar_to_vector3(t_vector3 init, double scale)
{
	return ((t_vector3){
		init.x + scale,
		init.y + scale,
		init.z + scale
	});
}
