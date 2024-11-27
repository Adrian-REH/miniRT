/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:32 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:20:41 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	control_d(Scene *scene)
{
	t_vector3	axis_of_rotation;

	axis_of_rotation = \
			cross_v3(scene->cameras->dir, scene->cameras->horizontal);
	normalize(&axis_of_rotation);
	if (scene->pos_obj->rot[scene->pos_obj->type])
		scene->pos_obj->rot[scene->pos_obj->type](scene, axis_of_rotation, 10);
	render_scene(scene, N_SAMPLING);
}
