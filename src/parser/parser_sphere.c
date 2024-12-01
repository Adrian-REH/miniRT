/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:42 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 17:38:19 by razamora         ###   ########.fr       */
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
	diameter = atof(data);
	return (diameter);
}

static void	validate_params(char **data)
{
	if (!data[1] || !data[2] || !data[3])
	{
		printf("Error: Parametros incompletos en la esfera\n");
		exit(1);
	}
}

int	parser_sphere(t_scene *scene, char **data)
{
	t_vector3	center;
	t_color		color;

	color = (t_color){0, 0, 0, 0};
	center = (t_vector3){0, 0, 0};
	validate_params(data);
	scene->spheres = ft_realloc(scene->spheres, sizeof(t_sphere) * \
		scene->n_spheres, sizeof(t_sphere) * (scene->n_spheres + 2));
	center = ft_coordinate(data[1]);
	color = ft_color(data[3]);
	scene->spheres[scene->n_spheres].mater_prop.color = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->spheres[scene->n_spheres].mater_prop.absorption[R] = \
	1 - scene->spheres[scene->n_spheres].mater_prop.color.r;
	scene->spheres[scene->n_spheres].mater_prop.absorption[G] = \
	1 - scene->spheres[scene->n_spheres].mater_prop.color.g;
	scene->spheres[scene->n_spheres].mater_prop.absorption[B] = \
	1 - scene->spheres[scene->n_spheres].mater_prop.color.b;
	scene->spheres[scene->n_spheres].center = center;
	scene->spheres[scene->n_spheres].mater_prop.glssns = 0.95;
	scene->spheres[scene->n_spheres].mater_prop.reflect = 0;
	scene->spheres[scene->n_spheres].radius = diamenter_sphere(data[2]) / 2;
	scene->n_spheres++;
	return (1);
}
