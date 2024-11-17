/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:10 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 22:54:44 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../main.h"

int	parser_light(Scene *scene, char **data)
{

	Vector3		point = {0, 0, 0};
	double		ratio = 0;
	Color		color = {0, 0, 0};


	scene->lights = malloc(sizeof(Light));
	if (!scene->lights)
		return NULL;
	point = ft_coordinate(data[1]);
	color = ft_color(data[3]);
	scene->lights->color = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
//	scene->lights->color = int_to_color(0xFFFFFF);
	scene->lights->point =  point;
	scene->lights->ratio =  ft_limit(0, 1, ft_ratio(data[2]));	

	// printf("----> |%f| |%f| |%f| |%f|\n", scene->lights->point.x, scene->lights->point.y, scene->lights->point.z, scene->lights->ratio);
	// printf("----> |%f| |%f| |%f|\n", scene->lights->color->r, scene->lights->color->g, scene->lights->color->b);
	//exit (1);
}