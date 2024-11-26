/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:19 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:21:21 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	control_up(Scene *scene)
{
	Vector3	tmp;

	tmp = scalev3(scene->cameras->dir, 1);
	if (scene->pos_obj->pos[scene->pos_obj->type])
		scene->pos_obj->pos[scene->pos_obj->type](scene, tmp);
	render_scene(scene, N_SAMPLING);
}
