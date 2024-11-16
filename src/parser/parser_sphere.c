/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:42 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 16:05:43 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_sphere(Scene *scene, char **data)
{
	Vector3 center = {0, 0, 0};
	double radius = 0;
	Color color = {0, 0, 0};
/*
Sphere
sp
0,0,20
20
255,0,0
*/
printf(" spehere ----->1|%s| 2|%s| 3|%s| 4|%s| \n", data[0], data[1], data[2], data[3]);

	char **args = ft_split(data[1], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain coor x, x ,y\n", data[1]);
		exit(1);
	}
	scene->spheres = malloc(sizeof(Sphere) * 1);

	center.x = atof(args[0]);
	center.y = atof(args[1]);
	center.z = atof(args[2]);

	ft_free_p2(args);

	if (data[2] == NULL)
	{
		printf("Error: %s not contain radius\n", data[2]);
		exit(1);
	}
	radius = atof(data[2]);

	args = ft_split(data[3], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain color r, g, b\n", data[3]);
		exit(1);
	}

	color.r = atof(args[0]);
	color.g = atof(args[1]);
	color.b = atof(args[2]);
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


	scene->spheres[scene->n_spheres].mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->spheres[scene->n_spheres].mater_prop.absorption[R] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r;
	scene->spheres[scene->n_spheres].mater_prop.absorption[G] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g;
	scene->spheres[scene->n_spheres].mater_prop.absorption[B] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b;
	//scene->n_spheres++;
	scene->spheres[scene->n_spheres].center = center;
	scene->spheres[scene->n_spheres].radius = radius;

	
	//ft_bzero(&scene->spheres, sizeof(Plane));
	return (1);
	// scene->spheres = malloc(sizeof(Sphere) * 2);
	// scene->spheres[scene->n_spheres].center = (Vector3){0, 0, 3};
	// scene->spheres[scene->n_spheres].radius = 1.5;
	// scene->spheres[scene->n_spheres].mater_prop.vColor = int_to_color(0xC41414);
	// scene->spheres[scene->n_spheres].mater_prop.absorption[R] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r ;
	// scene->spheres[scene->n_spheres].mater_prop.absorption[G] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g ;
	// scene->spheres[scene->n_spheres].mater_prop.absorption[B] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b ;
	// scene->n_spheres++;
	// scene->spheres[scene->n_spheres].center = (Vector3){0, -5, 3};
	// scene->spheres[scene->n_spheres].radius = 0.2;
	// scene->spheres[scene->n_spheres].mater_prop.vColor = int_to_color(0xFFFFFF);
	// scene->spheres[scene->n_spheres].mater_prop.absorption[R] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r ;
	// scene->spheres[scene->n_spheres].mater_prop.absorption[G] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g ;
	// scene->spheres[scene->n_spheres].mater_prop.absorption[B] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b ;

}