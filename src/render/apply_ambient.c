/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:40 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:13:40 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

Color	apply_ambient(const RenderContext *ctx)
{
	Color	current_color;

	current_color = illuminate_surface(int_to_color(0), \
		ctx->scene->ambient->color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, \
		ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(&current_color, ctx->mater_prop.vColor, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, \
		ctx->mater_prop);
	normalize_color(&current_color);
	return (current_color);
}
