/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:18 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 17:20:18 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_camera(Scene *scene, char **data)
{
	Vector3	coord = {0, 0, 0};
	Vector3	dir = {0, 0, 0};
	double	fov;

	Camera camera;
	
	printf("Camera\n");
	printf("CAmera ------->: |%s| |%s| |%s| |%s|",data[0],data[1],data[2], data[3]);

	//exit(1);
	char **args = ft_split(data[1], ',');


	//printf("camera----> %s %s %s\n", args[0], args[1], args[2]);
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s no es un typo valido\n", data[1]);
		exit(1);
	}
	scene->cameras = malloc(sizeof(Camera));

	coord = ft_coordinate(data[1]);
	
	args = ft_split(data[2], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s no es un typo valido\n", data[2]);
		exit(1);
	}
	dir = ft_normalizate(data[2]);
	printf("----> dir: (%f, %f, %f)\n", dir.x, dir.y, dir.z);
	
	fov = atof(data[3]);
	if (fov < 0 || fov > 180)
	{
		printf("Error: %s no es un typo valido\n", data[3]);
		exit(1);
	}
	printf("----> fov: %f\n", fov);
	scene->cameras->pos = coord;
	scene->cameras->dir = dir;
	scene->cameras->fov = fov;
	// scene->cameras = malloc(sizeof(Camera));
	// scene->cameras->pos = (Vector3){0, 0, 30};
	// // Ajusta el tamaño del plano de proyección en función de la relación de aspecto
	// scene->cameras->aspect_ratio = (double)WINX/WINY;
	// double fov = 50;
	scene->cameras->plane_distance = tan((fov / 2) * (PI / 180));
	scene->cameras->plane_half_width = scene->cameras->aspect_ratio * scene->cameras->plane_distance; // Ajuste según el aspecto
	scene->cameras->plane_half_height = 1.0 * scene->cameras->plane_distance;         // Altura basada en la distancia
	
	// PREGUNTAR A ADRIAN
	scene->cameras->dir = (Vector3){0, 0, -1}; // Apunta hacia el -Z
	scene->cameras->horizontal = (Vector3){1, 0, 0};      // Apunta hacia la derecha
	scene->cameras->vertical = (Vector3){0, -1, 0};         // Apunta hacia arriba
}