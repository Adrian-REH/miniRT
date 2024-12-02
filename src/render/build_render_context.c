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

t_rend_ctx	build_render_ctx(t_scene *scene, t_mater_prop mater_prop, \
t_vector3 normal, t_vector3 hit_pt)
{
	t_rend_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_rend_ctx));
	ctx = (t_rend_ctx){
		.scene = scene,
		.mater_prop = mater_prop,
		.normal = normal,
		.hit_pt = hit_pt,
		.rayl = (t_ray){{0, 0, 0}, {0, 0, 0}},
		.cam_dir = norm_subtract(scene->cameras->pos, hit_pt),
		.funcs = {
		.calculate_intensity = calculate_intensity,
		.calculate_attenuation = calculate_attenuation,
		.reflect = reflect
	}};
	return (ctx);
}
