/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:44 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:27:00 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static t_light_ctx	build_light_ctx(const t_rend_ctx *ctx, \
t_vector3 *light_dir, t_vector3 *cam_dir)
{
	t_light_ctx	l_ctx;

	ft_bzero(&l_ctx, sizeof(t_light_ctx));
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

t_color	apply_lighting(const t_rend_ctx *ctx, \
t_vector3 *light_dir, t_vector3 *cam_dir)
{
	t_light_ctx	l_ctx;
	t_color		current_color;

	l_ctx = build_light_ctx(ctx, light_dir, cam_dir);
	current_color = illuminate_surface(int_to_color(0), \
		ctx->scene->ambient->color, \
			fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), \
				ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, l_ctx.light->color, \
		fmax(fmin(1 - (l_ctx.light->ratio * l_ctx.diffuse_intensity), 1.0), 0), \
			ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, l_ctx.light->color, \
		fmax(fmin(1 - (l_ctx.light->ratio * l_ctx.specular), 1.0), 0), \
			ctx->mater_prop);
	normalize_color(&current_color);
	current_color = illuminate_surface(current_color, ctx->mater_prop.color, \
		fmax(fmin(1 - (l_ctx.full_phong), 1.0), 0), ctx->mater_prop);
	normalize_color(&current_color);
	return (current_color);
}
