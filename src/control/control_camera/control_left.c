/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:37 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:20:39 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	control_left(Scene *scene)
{
	Vector3	tmp;

	tmp = scalev3(scene->cameras->horizontal, -1);
	if (scene->pos_obj->pos[scene->pos_obj->type])
		scene->pos_obj->pos[scene->pos_obj->type](scene, tmp);
	render_scene(scene, N_SAMPLING);
}
