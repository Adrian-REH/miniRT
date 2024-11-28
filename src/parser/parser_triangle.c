/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:34 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 19:26:16 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_triangle(t_scene *scene, char **data)
{
	t_color		color;
	t_triangle	triangle;

	color = (t_color){0, 0, 0, 0};
	scene->triangles = ft_realloc(scene->triangles, sizeof(t_triangle) * \
	scene->n_triangles, sizeof(t_triangle) * (scene->n_triangles + 2));
	color = ft_color(data[4]);
	triangle = scene->triangles[scene->n_triangles];
	triangle.vertex[0] = ft_coordinate(data[1]);
	triangle.vertex[1] = ft_coordinate(data[2]);
	triangle.vertex[2] = ft_coordinate(data[3]);
	triangle.p_triangle.normal = cross_v3(\
	norm_subtract(triangle.vertex[0], triangle.vertex[1]), \
	norm_subtract(triangle.vertex[0], triangle.vertex[2]));
	triangle.p_triangle.point = triangle.vertex[0];
	triangle.mater_prop.color = rgb_to_color(color.r, color.g, color.b);
	triangle.mater_prop.reflect = 0;
	triangle.mater_prop.glssns = 0.95;
	triangle.mater_prop.absorption[R] = 1 - triangle.mater_prop.color.r;
	triangle.mater_prop.absorption[G] = 1 - triangle.mater_prop.color.g;
	triangle.mater_prop.absorption[B] = 1 - triangle.mater_prop.color.b;
	scene->triangles[scene->n_triangles] = triangle;
	scene->n_triangles++;
	return (0);
}
