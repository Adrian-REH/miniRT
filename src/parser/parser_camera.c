/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:18 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 18:36:33 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	validar_params(char **data)
{
	if (!data[1] || !data[2] || !data[3])
	{
		printf("Error: Parametros incompletos en la camara\n");
		exit(1);
	}
}

static void	there_are_camera(t_scene *scene)
{
	if (scene->cameras)
	{
		printf("Hay varias camaras en la escena\n");
		terminate_program(scene);
	}
}

int	parser_camera(t_scene *scene, char **data)
{
	double		fov;
	t_vector3	tmp;
	t_vector3	right;

	if (scene->cameras)
		there_are_camera(scene);
	if (!scene->width || !scene->height)
		scene->height = ((scene->width = 800), 800);
	validar_params(data);
	scene->cameras = malloc(sizeof(t_camera));
	fov = ft_limit(0, 180, atof(data[3]));
	scene->cameras->pos = ft_coordinate(data[1]);
	scene->cameras->dir = stonorm(data[2]);
	scene->cameras->fov = fov;
	scene->cameras->aspect_ratio = (double)scene->width / scene->height;
	scene->cameras->plane_distance = tan((fov / 2) * (M_PI / 180));
	scene->cameras->plane_half_width = scene->cameras->aspect_ratio * \
		scene->cameras->plane_distance;
	scene->cameras->plane_half_height = 1.0 * scene->cameras->plane_distance;
	tmp = (t_vector3){0, 1, 0};
	right = cross_v3(tmp, scene->cameras->dir);
	scene->cameras->horizontal = right;
	scene->cameras->vertical = cross_v3(scene->cameras->dir, right);
	return (0);
}
