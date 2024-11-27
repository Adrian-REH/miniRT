/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rfc_render_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:14:33 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 20:56:05 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_rfc_render_fun(Scene *scene)
{
	scene->rfc[0] = (int (*)(void *, Ray, int i, int))render_reflect_plane;
	scene->rfc[1] = (int (*)(void *, Ray, int i, int))render_reflect_sphere;
	scene->rfc[2] = (int (*)(void *, Ray, int i, int))render_reflect_triangle;
	scene->rfc[3] = (int (*)(void *, Ray, int i, int))render_reflect_cylinder;
	scene->rfc[4] = NULL;
}
