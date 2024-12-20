/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:57 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 17:38:02 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
static void	validar_params(char **data)
{
	if (!data[1] || !data[2] || !data[3])
	{
		printf("Error: Parametros incompletos en el plano\n");
		exit(1);
	}
}

int	parser_plane(t_scene *scene, char **data)
{
	t_plane	plane_null;
	t_plane	plane;
	t_color	color;

	color = (t_color){0, 0, 0, 0};
	validar_params(data);
	scene->planes = ft_realloc(scene->planes, sizeof(t_plane) * \
		scene->n_planes, sizeof(t_plane) * (scene->n_planes + 2));
	color = ft_color(data[3]);
	plane = scene->planes[scene->n_planes];
	plane.mater_prop.color = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	plane.mater_prop.reflect = 1;
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
