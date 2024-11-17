/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalizate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:37:04 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 23:03:38 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Vector3	ft_normalizate(char *argv)
{
	Vector3 norm;
	char **args = ft_split(argv, ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain norme x, x ,y\n");
		exit(1);
	}
	norm.x = ft_limit(-1,1,atof(args[0]));
	norm.y = ft_limit(-1,1,atof(args[1]));
	norm.z = ft_limit(-1,1,atof(args[2]));
	ft_free_p2(args);
	// if (norm.x < -1 || norm.x > 1)
	// {
	// 	printf("Error: %s not contain normal x, x ,y\n");
	// 	exit(1);
	// }
	// if (norm.y < -1 || norm.y > 1)
	// {
	// 	printf("Error: %s not contain normal x, x ,y\n");
	// 	exit(1);
	// }
	// if (norm.z < -1 || norm.z > 1)
	// {
	// 	printf("Error: %s not contain normal x, x ,y\n");
	// 	exit(1);
	// }
	return (norm);
}