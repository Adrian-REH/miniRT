/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:14 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 17:37:02 by razamora         ###   ########.fr       */
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

static void	validate_params(char **data)
{
	if (!data[1] || !data[2] || !data[3] || !data[4] || !data[5])
	{
		printf("Error: Parametros incompletos en el cilindro\n");
		exit(1);
	}
}

int	parser_cylinder(t_scene *scene, char **data)
{
	t_cylinder	cylinder_null;
	t_cylinder	cylinder;
	t_color		color;

	color = (t_color){0, 0, 0, 0};
	validate_params(data);
	scene->cylinders = ft_realloc(scene->cylinders, sizeof(t_cylinder) * \
	scene->n_cylinders, sizeof(t_cylinder) * (scene->n_cylinders + 2));
	cylinder.center = ft_coordinate(data[1]);
	cylinder.axis = stonorm(data[2]);
	cylinder.diameter = diamenter_cylinder(data[3]);
	cylinder.height = height_cylinder(data[4]);
	color = ft_color(data[5]);
	cylinder.mater_prop.color = \
	rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	cylinder.mater_prop.reflect = 1;
	cylinder.mater_prop.glssns = 0.95;
	cylinder.mater_prop.absorption[R] = 1 - cylinder.mater_prop.color.r;
	cylinder.mater_prop.absorption[G] = 1 - cylinder.mater_prop.color.g;
	cylinder.mater_prop.absorption[B] = 1 - cylinder.mater_prop.color.b;
	scene->cylinders[scene->n_cylinders] = cylinder;
	scene->n_cylinders += (ft_bzero(&cylinder_null, sizeof(t_cylinder)), 1);
	scene->cylinders[scene->n_cylinders] = cylinder_null;
	return (0);
}
