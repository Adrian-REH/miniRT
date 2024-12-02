/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:37 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 17:32:05 by razamora         ###   ########.fr       */
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

static void	validate_params(char **data)
{
	if (!data[1] || !data[2] || !data[3] || !data[4])
	{
		printf("Error: Parametros incompletos en el cuadrado\n");
		exit(1);
	}
}

int	parser_square(t_scene *scene, char **data)
{
	t_color		color;
	t_square	square;

	color = (t_color){0, 0, 0, 0};
	validate_params(data);
	scene->squares = ft_realloc(scene->squares, sizeof(t_square) * \
		scene->n_squares, sizeof(t_square) * (scene->n_squares + 2));
	color = ft_color(data[4]);
	square = scene->squares[scene->n_squares];
	square.center = ft_coordinate(data[1]);
	square.normal = stonorm(data[2]);
	square.side = side_square(data[3]);
	square.mater_prop.color = \
		rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	square.mater_prop.absorption[R] = 1 - square.mater_prop.color.r;
	square.mater_prop.absorption[G] = 1 - square.mater_prop.color.g;
	square.mater_prop.absorption[B] = 1 - square.mater_prop.color.b;
	square.mater_prop.reflect = 0;
	square.mater_prop.glssns = 0.95;
	scene->squares[scene->n_squares] = square;
	scene->n_squares++;
	return (0);
}
