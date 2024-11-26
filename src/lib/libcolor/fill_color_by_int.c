/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_by_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:29:08 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	addint_to_color(Color *color, int src)
{
	if (color == NULL)
		return ;
	color->r = ((src >> 16) & 0xFF) / 255.0;
	color->g = ((src >> 8) & 0xFF) / 255.0;
	color->b = (src & 0xFF) / 255.0;
	color->color = src;
}

void	fillcolor_by_int(Color *color, int src)
{
	if (color == NULL)
		return ;
	color->r = ((src >> 16) & 0xFF) / 255.0;
	color->g = ((src >> 8) & 0xFF) / 255.0;
	color->b = (src & 0xFF) / 255.0;
	color->color = src;
}
