/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:14 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 12:36:25 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double diamenter_cylinder(char *data)
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

static double height_cylinder(char *data)
{
	double height;
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

	Vector3		center =  {0.0, 0.0, 0.0};
	Vector3		axis = {0.0, 0.0, 0.0};
	double	diameter;
	double	height;
	Color color = {0, 0, 0};

	Cylinder cylinder_null;
	scene->cylinders = ft_realloc(scene->cylinders, sizeof(Cylinder) * scene->n_cylinders, sizeof(Cylinder) * (scene->n_cylinders + 2));

	center = ft_coordinate(data[1]);
	axis = ft_normalizate(data[2]);
	diameter = diamenter_cylinder(data[3]);
	height = height_cylinder(data[4]);
	colornormal_to_int(color);
	scene->cylinders[scene->n_cylinders].center = center;
	scene->cylinders[scene->n_cylinders].axis = axis;
	scene->cylinders[scene->n_cylinders].diameter = diameter;
	scene->cylinders[scene->n_cylinders].height = height;
	scene->cylinders[scene->n_cylinders].mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
}
