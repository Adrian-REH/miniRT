/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:22 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 22:56:49 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_ambient(Scene *scene, char **data)
{

	Color color = {0, 0, 0};
	scene->ambient = malloc(sizeof(Ambient));
	scene->ambient->ratio = ft_limit(0, 1, ft_ratio(data[1]));
	color = ft_color(data[2]);  
	scene->ambient->color = rgb_to_color(color.r, color.g, color.b);
}