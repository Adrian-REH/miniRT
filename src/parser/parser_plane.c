/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:57 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 15:35:58 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
int	parser_plane(Scene *scene, char **data)
{
	Plane	plane_null;
	Plane	plane;
	Color	color;

	color = (Color){0, 0, 0, 0};
	scene->planes = ft_realloc(scene->planes, sizeof(Plane) * \
		scene->n_planes, sizeof(Plane) * (scene->n_planes + 2));
	color = ft_color(data[3]);
	plane = scene->planes[scene->n_planes];
	plane.mater_prop.vColor = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	plane.mater_prop.reflect = 1;
	plane.mater_prop.absorption[R] = 1 - plane.mater_prop.vColor->r;
	plane.mater_prop.absorption[G] = 1 - plane.mater_prop.vColor->g;
	plane.mater_prop.absorption[B] = 1 - plane.mater_prop.vColor->b;
	plane.normal = stonorm(data[2]);
	plane.point = ft_coordinate(data[1]);
	scene->planes[scene->n_planes] = plane;
	scene->n_planes++;
	ft_bzero(&plane_null, sizeof(Plane));
	scene->planes[scene->n_planes] = plane_null;
	return (0);
}
