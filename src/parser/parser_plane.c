/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:57 by razamora          #+#    #+#             */
/*   Updated: 2024/11/30 18:55:31 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
int	parser_plane(t_scene *scene, char **data)
{
	t_plane	plane_null;
	t_plane	plane;
	t_color	color;

	color = (t_color){0, 0, 0, 0};
	scene->planes = ft_realloc(scene->planes, sizeof(t_plane) * \
		scene->n_planes, sizeof(t_plane) * (scene->n_planes + 2));
	color = ft_color(data[3]);
	plane = scene->planes[scene->n_planes];
	plane.mater_prop.color = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	plane.mater_prop.reflect = 0;
	plane.mater_prop.glssns = 0.95;
	plane.mater_prop.absorption[R] = 1 - plane.mater_prop.color.r;
	plane.mater_prop.absorption[G] = 1 - plane.mater_prop.color.g;
	plane.mater_prop.absorption[B] = 1 - plane.mater_prop.color.b;
	plane.normal = stonorm(data[2]);
	plane.point = ft_coordinate(data[1]);
	scene->planes[scene->n_planes] = plane;
	scene->n_planes++;
	ft_bzero(&plane_null, sizeof(t_plane));
	scene->planes[scene->n_planes] = plane_null;
	return (0);
}
