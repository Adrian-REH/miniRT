/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:50 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:21:07 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_render_fun(Scene *scene)
{
	scene->render[0] = (int (*)(void *, t_vector3, int))render_plane;
	scene->render[1] = (int (*)(void *, t_vector3, int))render_sphere;
	scene->render[2] = (int (*)(void *, t_vector3, int))render_triangle;
	scene->render[3] = (int (*)(void *, t_vector3, int))render_cylinder;
	scene->render[4] = NULL;
}
