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

static double	diamenter_sphere(char *data)
{
	double	diameter;

	if (data == NULL)
	{
		printf("Error: %s not contain diameter\n", data);
		exit(1);
	}
	diameter = atof(data);//FT_ATOF
	return (diameter);
}

int	parser_sphere(Scene *scene, char **data)
{
	Vector3	center;
	Color	color;

	color = (Color){0, 0, 0};
	center = (Vector3){0, 0, 0};
	scene->spheres = ft_realloc(scene->spheres, sizeof(Sphere) * \
		scene->n_spheres, sizeof(Sphere) * (scene->n_spheres + 2));
	center = ft_coordinate(data[1]);
	color = ft_color(data[3]);
	scene->spheres[scene->n_spheres].mater_prop.vColor = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->spheres[scene->n_spheres].mater_prop.absorption[R] = \
	1 - scene->spheres[scene->n_spheres].mater_prop.vColor->r;
	scene->spheres[scene->n_spheres].mater_prop.absorption[G] = \
	1 - scene->spheres[scene->n_spheres].mater_prop.vColor->g;
	scene->spheres[scene->n_spheres].mater_prop.absorption[B] = \
	1 - scene->spheres[scene->n_spheres].mater_prop.vColor->b;
	scene->spheres[scene->n_spheres].center = center;
	scene->spheres[scene->n_spheres].radius = diamenter_sphere(data[2]) / 2;
	scene->n_spheres++;
	return (1);
}
