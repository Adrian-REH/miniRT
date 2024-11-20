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
	Vector3 tmp;
	Vector3 right;
	scene->cameras = malloc(sizeof(Camera));
	coord = ft_coordinate(data[1]);
	dir = stonorm(data[2]);
	fov = ft_limit(0,180,atof(data[3]));
	scene->cameras->pos = coord;
	scene->cameras->dir = dir;
	scene->cameras->fov = fov;
	scene->cameras->aspect_ratio = (double)scene->width/scene->height; 
	scene->cameras->plane_distance = tan((fov / 2) * (M_PI / 180));
	scene->cameras->plane_half_width = scene->cameras->aspect_ratio * scene->cameras->plane_distance; // Ajuste según el aspecto
	scene->cameras->plane_half_height = 1.0 * scene->cameras->plane_distance;         // Altura basada en la distancia
	tmp = (Vector3){0, 1, 0};
	right = cross_v3(tmp, dir);
	scene->cameras->horizontal = right;
	scene->cameras->vertical = cross_v3(dir, right);
}