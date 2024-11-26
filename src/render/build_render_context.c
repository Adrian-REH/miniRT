/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_render_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:44 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:23:45 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

RenderContext	build_render_ctx(Scene *scene, MaterialProperties mater_prop, \
Vector3 normal, Vector3 hit_pt)
{
	RenderContext	ctx;

	ft_bzero(&ctx, sizeof(RenderContext));
	ctx = (RenderContext){
		.scene = scene,
		.mater_prop = mater_prop,
		.normal = normal,
		.hit_pt = hit_pt,
		.rayl = (Ray){{0, 0, 0}, {0, 0, 0}},
		.cam_dir = norm_subtract(scene->cameras->pos, hit_pt),
		.funcs = {
		.calculate_intensity = calculate_intensity,
		.calculate_attenuation = calculate_attenuation,
		.reflect = reflect
	}};
	return (ctx);
}
