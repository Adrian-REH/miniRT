/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:31:28 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:24:36 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Color	rgb_to_color(int r, int g, int b)
{
	Color	color;

	color.r = (double)(r / 255.0);
	color.g = (double)(g / 255.0);
	color.b = (double)(b / 255.0);
	color.color = colornormal_to_int(color);
	return (color);
}
