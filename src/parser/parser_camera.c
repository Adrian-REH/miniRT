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
	double	fov;
	Vector3	tmp;
	Vector3	right;

	scene->cameras = malloc(sizeof(Camera));
	fov = ft_limit(0, 180, atof(data[3]));
	scene->cameras->pos = ft_coordinate(data[1]);
	scene->cameras->dir = stonorm(data[2]);
	scene->cameras->fov = fov;
	scene->cameras->aspect_ratio = (double)scene->width / scene->height;
	scene->cameras->plane_distance = tan((fov / 2) * (M_PI / 180));
	scene->cameras->plane_half_width = scene->cameras->aspect_ratio * \
		scene->cameras->plane_distance;
	scene->cameras->plane_half_height = 1.0 * scene->cameras->plane_distance;
	tmp = (Vector3){0, 1, 0};
	right = cross_v3(tmp, scene->cameras->dir);
	scene->cameras->horizontal = right;
	scene->cameras->vertical = cross_v3(scene->cameras->dir, right);
}
