/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:34 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:35 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	rot_camera(Scene *scene, Vector3 dir, int ang)
{
	scene->cameras->dir = rotate_v3(scene->cameras->dir, dir, ang);
	scene->cameras->horizontal = \
		rotate_v3(scene->cameras->horizontal, dir, ang);
	scene->cameras->vertical = rotate_v3(scene->cameras->vertical, dir, ang);
	normalize(&scene->cameras->dir);
	normalize(&scene->cameras->vertical);
	normalize(&scene->cameras->horizontal);
}

void	pos_camera(Scene *scene, Vector3 dir)
{
	Camera	*camera;

	camera = scene->cameras;
	camera->pos = add_vector3_to_vector3(camera->pos, dir);
}
