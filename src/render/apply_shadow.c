/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:47 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:26:45 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

Color	apply_shadow(const RenderContext *ctx, t_vector3 *light_dir, \
t_vector3 *cam_dir, t_vector3 *opac_pt)
{
	Color	ambient_color;
	Color	current_color;

	(void)opac_pt;
	(void)light_dir;
	(void)cam_dir;
	ambient_color = int_to_color(0);
	current_color = illuminate_surface(ambient_color, \
		ctx->scene->ambient->color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
		ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(ambient_color, ctx->mater_prop.vColor, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
		ctx->mater_prop);
	normalize_color(&current_color);
	current_color = darken_surface(&current_color, \
		(ctx->scene->ambient->ratio));
	normalize_color(&current_color);
	return (current_color);
}
