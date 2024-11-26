/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:14 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 19:53:51 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	diamenter_cylinder(char *data)
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

static double	height_cylinder(char *data)
{
	double	height;

	if (data == NULL)
	{
		printf("Error: %s not contain height\n", data);
		exit(1);
	}
	height = atof(data);
	return (height);
}

int	parser_cylinder(Scene *scene, char **data)
{
	Cylinder	cylinder_null;
	Cylinder	cylinder;
	Color		color;

	color = (Color){0, 0, 0, 0};
	if (ft_sarrsize(data) != 6)
		terminate_program(scene);
	scene->cylinders = ft_realloc(scene->cylinders, sizeof(Cylinder) * \
	scene->n_cylinders, sizeof(Cylinder) * (scene->n_cylinders + 2));
	cylinder.center = ft_coordinate(data[1]);
	cylinder.axis = stonorm(data[2]);
	cylinder.diameter = diamenter_cylinder(data[3]);
	cylinder.height = height_cylinder(data[4]);
	color = ft_color(data[5]);
	cylinder.mater_prop.vColor = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	cylinder.mater_prop.reflect = 1;
	cylinder.mater_prop.absorption[R] = 1 - cylinder.mater_prop.vColor.r;
	cylinder.mater_prop.absorption[G] = 1 - cylinder.mater_prop.vColor.g;
	cylinder.mater_prop.absorption[B] = 1 - cylinder.mater_prop.vColor.b;
	scene->cylinders[scene->n_cylinders] = cylinder;
	scene->n_cylinders++;
	ft_bzero(&cylinder_null, sizeof(Cylinder));
	scene->cylinders[scene->n_cylinders] = cylinder_null;
	return (0);
}
