/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:40 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:27:12 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_color	apply_ambient(const t_rend_ctx *ctx)
{
	t_color	current_color;

	current_color = illuminate_surface(int_to_color(0), \
		ctx->scene->ambient->color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
		ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, ctx->mater_prop.color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), ctx->mater_prop);
	normalize_color(&current_color);
	return (current_color);
}
