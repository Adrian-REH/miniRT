/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:09 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:21:14 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/**
 * Controlo la posicion del objeto
 */
void	control_down(Scene *scene)
{
	t_vector3	tmp;

	tmp = scalev3(scene->cameras->dir, -1);
	if (scene->pos_obj->pos[scene->pos_obj->type])
		scene->pos_obj->pos[scene->pos_obj->type](scene, tmp);
	render_scene(scene, N_SAMPLING);
}
