/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:26 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 17:17:18 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

double ft_limit(double min, double max, double val)
{
	if ( max < val && val > min)
		return val;
	printf("Error el valor no se encuentre entre los limites [%f, %f]", min, max);
	//llamar a una funcion que libere
	exit(1);
}
double ft_radio(char *str)
{
	double	radio;

	radio = atof(str);
	if (radio < 0 || radio > 1)
	{
		printf("Error: %s Range Radio should be bewteen 0 to 1\n", str);
		exit(1);
	}
	return (radio);
}

Vector3	ft_coordinate(char *argv)
{
	Vector3 coord;

	char **args = ft_split(argv, ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain coor x, x ,y\n");
		exit(1);
	}
	coord.x = atof(args[0]);
	coord.y = atof(args[1]);
	coord.z = atof(args[2]);
	ft_free_p2(args);
	return (coord);
}

Vector3	ft_normalizate(char *argv)
{
	Vector3 norm;
	char **args = ft_split(argv, ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain coor x, x ,y\n");
		exit(1);
	}
	norm.x = atof(args[0]);
	norm.y = atof(args[1]);
	norm.z = atof(args[2]);
	ft_free_p2(args);
	if (norm.x < -1 || norm.x > 1)
	{
		printf("Error: %s not contain normal x, x ,y\n");
		exit(1);
	}
	if (norm.y < -1 || norm.y > 1)
	{
		printf("Error: %s not contain normal x, x ,y\n");
		exit(1);
	}
	if (norm.z < -1 || norm.z > 1)
	{
		printf("Error: %s not contain normal x, x ,y\n");
		exit(1);
	}
	return (norm);
}

