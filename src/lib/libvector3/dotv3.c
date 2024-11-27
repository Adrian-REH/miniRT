/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotv3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:25 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:25:26 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	dot(t_vector3 a, t_vector3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}
