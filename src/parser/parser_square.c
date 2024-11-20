/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:37 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 15:46:40 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"


static double side_square(char *data)
{
    double side;
    if (data == NULL)
    {
        printf("Error: %s not contain side\n", data);
        exit(1);
    }
    side = atof(data);
    return (side);
}

int	parser_square(Scene *scene, char **data)
{
    Vector3 center = {0, 0, 0};
    Vector3 normal = {0, 0, 0};
    double side = 0;
    Color color = {0, 0, 0};

	scene->squares = ft_realloc(scene->squares, sizeof(Square) * scene->n_squares, sizeof(Square) * (scene->n_squares + 2));
    center = ft_coordinate(data[1]);
    normal = stonorm(data[2]);
    side = side_square(data[3]);
    color = ft_color(data[4]);
    scene->squares->center = center;
    scene->squares->normal = normal;
    scene->squares->side = side;
    scene->squares->mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
    scene->squares[scene->n_squares].mater_prop.absorption[R] = 1 - scene->squares[scene->n_squares].mater_prop.vColor->r;
	scene->squares[scene->n_squares].mater_prop.absorption[G] = 1 - scene->squares[scene->n_squares].mater_prop.vColor->g;
	scene->squares[scene->n_squares].mater_prop.absorption[B] = 1 - scene->squares[scene->n_squares].mater_prop.vColor->b;
	scene->squares[scene->n_squares].mater_prop.reflect = 0;
    scene->n_squares++;
}