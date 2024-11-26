/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:37 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 20:50:12 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	side_square(char *data)
{
	double	side;

	if (data == NULL)
		(printf("Error: %s not contain side\n", data), exit(1));
	side = atof(data);
	return (side);
}

int	parser_square(Scene *scene, char **data)
{
	Color	color;
	Square	square;

	color = (Color){0, 0, 0, 0};
	scene->squares = ft_realloc(scene->squares, sizeof(Square) * \
		scene->n_squares, sizeof(Square) * (scene->n_squares + 2));
	color = ft_color(data[4]);
	square = scene->squares[scene->n_squares];
	square.center = ft_coordinate(data[1]);
	square.normal = stonorm(data[2]);
	square.side = side_square(data[3]);
	square.mater_prop.vColor = \
		rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	square.mater_prop.absorption[R] = 1 - square.mater_prop.vColor.r;
	square.mater_prop.absorption[G] = 1 - square.mater_prop.vColor.g;
	square.mater_prop.absorption[B] = 1 - square.mater_prop.vColor.b;
	square.mater_prop.reflect = 0;
	scene->squares[scene->n_squares] = square;
	scene->n_squares++;
	return (0);
}
