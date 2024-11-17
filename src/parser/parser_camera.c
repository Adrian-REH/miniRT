/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:18 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 22:17:44 by razamora         ###   ########.fr       */
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
	
	scene->cameras = malloc(sizeof(Camera));

	coord = ft_coordinate(data[1]);
	dir = ft_normalizate(data[2]);
	printf("----> dir: (%f, %f, %f)\n", dir.x, dir.y, dir.z);
	fov = ft_limit(0,180,atof(data[3]));
	printf("----> fov: %f\n", fov);
	scene->cameras->pos = coord;
	scene->cameras->dir = dir;
	scene->cameras->fov = fov;
	//Llegar una conclusion para obtener siempre primero el height y width antes de tocar la camara
	scene->cameras->aspect_ratio = scene->width / scene->height; 
	scene->cameras->plane_distance = tan((fov / 2) * (PI / 180));
	scene->cameras->plane_half_width = scene->cameras->aspect_ratio * scene->cameras->plane_distance; // Ajuste según el aspecto
	scene->cameras->plane_half_height = 1.0 * scene->cameras->plane_distance;         // Altura basada en la distancia
	scene->cameras->horizontal = (Vector3){1, 0, 0};      // Apunta hacia la derecha
	scene->cameras->vertical = (Vector3){0, -1, 0};         // Apunta hacia arriba
	// PREGUNTAR A ADRIAN
	scene->cameras->dir = (Vector3){0, 0, -1}; // Apunta hacia el -Z
}