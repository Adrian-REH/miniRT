/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:10 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 17:31:29 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	validar_params(char **data)
{
	if (!data[1] || !data[2] || !data[3])
	{
		printf("Error: Parametros incompletos en la luz\n");
		exit(1);
	}
}

int	parser_light(t_scene *scene, char **data)
{
	t_vector3	point;
	t_color		color;

	point = (t_vector3){0, 0, 0};
	color = (t_color){0, 0, 0, 0};
	validar_params(data);
	scene->lights = ft_realloc(scene->lights, sizeof(t_light) * \
		scene->n_lights, sizeof(t_light) * (scene->n_lights + 2));
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
