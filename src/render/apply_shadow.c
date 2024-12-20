/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:47 by adherrer          #+#    #+#             */
/*   Updated: 2024/12/01 16:12:01 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_color	apply_shadow(const t_rend_ctx *ctx, t_vector3 *light_dir, \
t_vector3 *cam_dir, t_vector3 *opac_pt)
{
	t_color	ambient_color;
	t_color	current_color;

	(void)opac_pt;
	(void)light_dir;
	(void)cam_dir;
	ambient_color = int_to_color(0);
	current_color = illuminate_surface(ambient_color, \
		ctx->scene->ambient->color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
		ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(ambient_color, ctx->mater_prop.color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
		ctx->mater_prop);
	normalize_color(&current_color);
	current_color = darken_surface(&current_color, \
		(ctx->scene->ambient->ratio));
	normalize_color(&current_color);
	return (ambient_color);
}
