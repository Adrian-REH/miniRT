/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:42 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 13:51:54 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double diamenter_sphere(char *data)
{
	double diameter;
	if (data == NULL)
	{
		printf("Error: %s not contain diameter\n", data);
		exit(1);
	}
	diameter = atof(data);
	return (diameter);
}

int	parser_sphere(Scene *scene, char **data)
{
	Vector3 center = {0, 0, 0};
	Color color = {0, 0, 0};

	printf(" spehere ----->0|%s| 1|%s| 2|%s| 3|%s| 4|%s| \n", data[0], data[1], data[2], data[3]);
	
	//scene->spheres = malloc(sizeof(Sphere) * 1);
	scene->spheres = ft_realloc(scene->spheres, sizeof(Sphere) * scene->n_spheres, sizeof(Sphere) * (scene->n_spheres + 2));
	center = ft_coordinate(data[1]);
	color = ft_color(data[3]);
	scene->spheres[scene->n_spheres].mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->spheres[scene->n_spheres].mater_prop.absorption[R] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r;
	scene->spheres[scene->n_spheres].mater_prop.absorption[G] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g;
	scene->spheres[scene->n_spheres].mater_prop.absorption[B] = 1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b;
	scene->spheres[scene->n_spheres].center = center;
	scene->spheres[scene->n_spheres].radius = diamenter_sphere(data[2]);
	//scene->n_spheres++;
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