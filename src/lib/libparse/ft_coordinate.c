/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coordinate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:37:25 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:12:11 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	ft_coordinate(char *argv)
{
	t_vector3	coord;
	char		**args;

	args = ft_split(argv, ',');
	if (!args)
		return ((t_vector3){0, 0, 0});
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: Not contain coor x, x ,y\n");
		exit(1);
	}
	coord.x = atof(args[0]);
	coord.y = atof(args[1]);
	coord.z = atof(args[2]);
	ft_free_p2(args);
	return (coord);
}
