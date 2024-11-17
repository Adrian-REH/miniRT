/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coordinate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:37:25 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 21:46:22 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

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