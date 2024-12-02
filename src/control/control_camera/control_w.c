/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:21:24 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	control_w(t_scene *scene)
{
	t_vector3	axis_of_rotation;

	axis_of_rotation = \
		cross_v3(scene->cameras->dir, scene->cameras->vertical);
	normalize(&axis_of_rotation);
	if (scene->pos_obj->rot[scene->pos_obj->type])
		scene->pos_obj->rot[scene->pos_obj->type](scene, axis_of_rotation, 10);
	render_scene(scene, N_SAMPLING);
}
