/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_intersect_fun.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:19:21 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:21:38 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_intersect_fun(Scene *scene)
{
	scene->isc[PLANE] = \
		(int (*)(const void *, const void *, double *))intersect_plane;
	scene->isc[SPHERE] = \
		(int (*)(const void *, const void *, double *))intersect_sphere;
	scene->isc[TRIANGLE] = \
		(int (*)(const void *, const void *, double *))intersect_triangle;
	scene->isc[CYLINDER] = \
		(int (*)(const void *, const void *, double *))intersect_cylinder;
	scene->isc[4] = NULL;
}
