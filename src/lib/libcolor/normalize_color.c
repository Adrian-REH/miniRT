/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:32:18 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:32:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	normalize_color(t_color *color)
{
	color->r = fmax(0.0, fmin(1.0, color->r / 255.0));
	color->g = fmax(0.0, fmin(1.0, color->g / 255.0));
	color->b = fmax(0.0, fmin(1.0, color->b / 255.0));
}
