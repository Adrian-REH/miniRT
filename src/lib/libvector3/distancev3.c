/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distancev3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:27 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:25:28 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	distance(Vector3 init, Vector3 end)
{
	return (sqrt(pow(end.x - init.x, 2) + pow(end.y - init.y, 2) + \
	pow(end.z - init.z, 2)));
}
