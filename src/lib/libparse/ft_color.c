/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:44:12 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:11:06 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Color	ft_color(char *str)
{
	Color 	color;
	char	**args;

	args = ft_split(str, ',');

	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain some color r or g or b\n", str);
		exit(1);
	}
	printf("Color: 0|%s| 1|%s| 2|%s| \n", args[0], args[1], args[2]);
	color.r = ft_limit(0, 255, atof(args[0]));
	color.g = ft_limit(0, 255, atof(args[1]));
	color.b = atof(args[2]);
	return (color);
}