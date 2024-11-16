/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:10 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 16:53:31 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../main.h"

int	parser_light(Scene *scene, char **data)
{

	Vector3		point = {0, 0, 0};
	double	ratio = 0;
	Color color = {0, 0, 0};

/*

	Vector3	point;
	double	ratio;
	Color	*color;*/




	// printf("Light\n");
// |l| |-40,0,30| |0.7| |255,255,255
//	printf("----> |%s| |%s| |%s| |%s|\n", data[0], data[1], data[2], data[3]);



	scene->lights = malloc(sizeof(Light));

	char **args = ft_split(data[1], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain coor x, y ,z\n", data[1]);
		exit(1);
	}
	point.x = atof(args[0]);
	point.y = atof(args[1]);
	point.z = atof(args[2]);

	ft_free_p2(args);
	ratio = ft_radio(data[2]);
	args = ft_split(data[3], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain color r, g, b\n", data[3]);
		exit(1);
	}
	printf("----> |%s| |%s| |%s|\n", args[0], args[1], args[2]);
	color.r = atof(args[0]);
	color.g = atof(args[1]);
	color.b = atof(args[2]);
//printf("----> |%f| |%f| |%f|\n", color.r, color.g, color.b);


	if (color.r < 0 || color.r > 255)
	{
		printf("Error: %s  r outside color range\n", data[3]);
		exit(1);
	}
	if (color.g < 0 || color.g > 255)
	{
		printf("Error: %s g outside color range\n", data[3]);
		exit(1);
	}
	if (color.b < 0 || color.b > 255)
	{
		printf("Error: %s b outside color range\n", data[3]);
		exit(1);
	}

	
	scene->lights->color = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
//	scene->lights->color = int_to_color(0xFFFFFF);
	scene->lights->point =  point;
	scene->lights->ratio = ratio;

	// printf("----> |%f| |%f| |%f| |%f|\n", scene->lights->point.x, scene->lights->point.y, scene->lights->point.z, scene->lights->ratio);
	// printf("----> |%f| |%f| |%f|\n", scene->lights->color->r, scene->lights->color->g, scene->lights->color->b);
	//exit (1);
}