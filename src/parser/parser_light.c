/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:10 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 20:49:50 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_light(Scene *scene, char **data)
{
	t_vector3		point;
	Color		color;

	point = (t_vector3){0, 0, 0};
	color = (Color){0, 0, 0, 0};
	scene->lights = ft_realloc(scene->lights, sizeof(Light) * \
		scene->n_lights, sizeof(Light) * (scene->n_lights + 2));
	if (!scene->lights)
		return (0);
	point = ft_coordinate(data[1]);
	color = ft_color(data[3]);
	scene->lights->color = \
		rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->lights->point = point;
	scene->lights->ratio = ft_limit(0, 1, ft_ratio(data[2]));
	scene->n_lights++;
	return (0);
}
