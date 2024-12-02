/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:22 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 18:56:20 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	there_are_amb(t_scene *scene)
{
	if (scene->ambient)
	{
		printf("Hay varias luces ambientales en la escena\n");
		terminate_program(scene);
	}
}

int	parser_ambient(t_scene *scene, char **data)
{
	t_color	color;

	if (scene->ambient)
		there_are_amb(scene);
	color = (t_color){0, 0, 0, 0};
	scene->ambient = malloc(sizeof(t_mbient));
	scene->ambient->ratio = ft_limit(0, 1, ft_ratio(data[1]));
	color = ft_color(data[2]);
	scene->ambient->color = rgb_to_color(color.r, color.g, color.b);
	return (0);
}
