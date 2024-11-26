/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:44 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 10:33:36 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static s_light_ctx	build_light_ctx(const RenderContext *ctx, \
Vector3 *light_dir, Vector3 *cam_dir)
{
	s_light_ctx	l_ctx;

	ft_bzero(&l_ctx, sizeof(s_light_ctx));
	l_ctx.light = ctx->scene->lights;
	l_ctx.distance_light = distance(l_ctx.light->point, ctx->hit_pt);
	l_ctx.attenuation = ctx->funcs.calculate_attenuation(l_ctx.distance_light, \
		L_P_KC, L_P_KL, 0);
	l_ctx.diffuse_intensity = ctx->funcs.calculate_intensity(ctx->normal, \
		*light_dir);
	l_ctx.diffuse_intensity = fmax(fmin(l_ctx.diffuse_intensity, 1.0), 0);
	l_ctx.reflect_dir = ctx->funcs.reflect(*light_dir, ctx->normal);
	l_ctx.specular = specular_intensity(l_ctx.reflect_dir, *cam_dir, \
		SHININESS, KS);
	l_ctx.specular = fmax(fmin(l_ctx.specular, 1.0), 0.0);
	l_ctx.full_phong = l_ctx.light->ratio * l_ctx.specular * l_ctx.attenuation;
	l_ctx.full_phong *= l_ctx.diffuse_intensity * ctx->scene->ambient->ratio;
	return (l_ctx);
}

Color	apply_lighting(const RenderContext *ctx, \
Vector3 *light_dir, Vector3 *cam_dir)
{
	s_light_ctx	l_ctx;
	Color		current_color;

	l_ctx = build_light_ctx(ctx, light_dir, cam_dir);
	current_color = illuminate_surface(int_to_color(0), \
		*ctx->scene->ambient->color, \
			fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
				1, 0, ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, *l_ctx.light->color, \
		fmax(fmin(1 - (l_ctx.light->ratio * l_ctx.diffuse_intensity), 1.0), 0), \
			1, 0, ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, *l_ctx.light->color, \
		fmax(fmin(1 - (l_ctx.light->ratio * l_ctx.specular), 1.0), 0), 1, 0, \
			ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, *ctx->mater_prop.vColor, \
		fmax(fmin(1 - (l_ctx.full_phong), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(&current_color);
	return (current_color);
}
